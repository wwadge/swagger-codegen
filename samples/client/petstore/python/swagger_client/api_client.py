#!/usr/bin/env python
# coding: utf-8

"""Swagger generic API client. This client handles the client-
server communication, and is invariant across implementations. Specifics of
the methods and models for each application are generated from the Swagger
templates."""

from __future__ import absolute_import
from . import models
from .rest import RESTClient
from .rest import ApiException

import os
import re
import urllib
import json
import datetime
import mimetypes
import random
import tempfile

# python 2 and python 3 compatibility library
from six import iteritems

try:
  # for python3
  from urllib.parse import quote
except ImportError:
  # for python2
  from urllib import quote

from . import configuration

class ApiClient(object):
  """
  Generic API client for Swagger client library builds

  :param host: The base path for the server to call
  :param header_name: a header to pass when making calls to the API
  :param header_value: a header value to pass when making calls to the API
  """
  def __init__(self, host=configuration.host, header_name=None, header_value=None):
    self.default_headers = {}
    if header_name is not None:
      self.default_headers[header_name] = header_value
    self.host = host
    self.cookie = None
    # Set default User-Agent.
    self.user_agent = 'Python-Swagger'

  @property
  def user_agent(self):
    return self.default_headers['User-Agent']

  @user_agent.setter
  def user_agent(self, value):
    self.default_headers['User-Agent'] = value

  def set_default_header(self, header_name, header_value):
    self.default_headers[header_name] = header_value

  def call_api(self, resource_path, method, path_params=None, query_params=None, header_params=None,
               body=None, post_params=None, files=None, response_type=None, auth_settings=None):

    # headers parameters
    header_params = header_params or {}
    header_params.update(self.default_headers)
    if self.cookie:
      header_params['Cookie'] = self.cookie
    if header_params:
      header_params = self.sanitize_for_serialization(header_params)

    # path parameters
    if path_params:
      path_params = self.sanitize_for_serialization(path_params)
      for k, v in iteritems(path_params):
        replacement = quote(str(self.to_path_value(v)))
        resource_path = resource_path.replace('{' + k + '}', replacement)

    # query parameters
    if query_params:
      query_params = self.sanitize_for_serialization(query_params)
      query_params = {k: self.to_path_value(v) for k, v in iteritems(query_params)}

    # post parameters
    if post_params:
      post_params = self.prepare_post_parameters(post_params, files)
      post_params = self.sanitize_for_serialization(post_params)

    # auth setting
    self.update_params_for_auth(header_params, query_params, auth_settings)

    # body
    if body:
      body = self.sanitize_for_serialization(body)

    # request url
    url = self.host + resource_path

    # perform request and return response
    response_data = self.request(method, url, query_params=query_params, headers=header_params,
                                 post_params=post_params, body=body)

    self.last_response = response_data

    # deserialize response data
    if response_type:
      return self.deserialize(response_data, response_type)
    else:
      return None

  def to_path_value(self, obj):
    """
    Convert a string or object to a path-friendly value

    :param obj: object or string value

    :return string: quoted value
    """
    if type(obj) == list:
      return ','.join(obj)
    else:
      return str(obj)

  def sanitize_for_serialization(self, obj):
    """
    Sanitize an object for Request.

    If obj is None, return None.
    If obj is str, int, float, bool, return directly.
    If obj is datetime.datetime, datetime.date convert to string in iso8601 format.
    If obj is list, santize each element in the list.
    If obj is dict, return the dict.
    If obj is swagger model, return the properties dict.
    """
    if isinstance(obj, type(None)):
      return None
    elif isinstance(obj, (str, int, float, bool, tuple)):
      return obj
    elif isinstance(obj, list):
      return [self.sanitize_for_serialization(sub_obj) for sub_obj in obj]
    elif isinstance(obj, (datetime.datetime, datetime.date)):
      return obj.isoformat()
    else:
      if isinstance(obj, dict):
        obj_dict = obj
      else:
        # Convert model obj to dict except attributes `swagger_types`, `attribute_map`
        # and attributes which value is not None.
        # Convert attribute name to json key in model definition for request.
        obj_dict = {obj.attribute_map[key[1:]]: val
                    for key, val in iteritems(obj.__dict__)
                    if key != 'swagger_types' and key != 'attribute_map' and val is not None}
      return {key: self.sanitize_for_serialization(val)
              for key, val in iteritems(obj_dict)}

  def deserialize(self, response, response_type):
    """
    Derialize response into an object.

    :param response: RESTResponse object to be deserialized
    :param response_type: class literal for deserialzied object, or string of class name

    :return: deserialized object
    """
    # handle file downloading - save response body into a tmp file and return the instance
    if "file" == response_type:
      return self.__deserialize_file(response)

    # fetch data from response object
    try:
      data = json.loads(response.data)
    except ValueError:
      data = response.data

    return self.__deserialize(data, response_type)

  def __deserialize(self, data, klass):
    """
    :param data: dict, list or str
    :param klass: class literal, or string of class name

    :return: object
    """
    if data is None:
      return None

    if type(klass) == str:
      if 'list[' in klass:
        sub_kls = re.match('list\[(.*)\]', klass).group(1)
        return [self.__deserialize(sub_data, sub_kls) for sub_data in data]

      if 'dict(' in klass:
        sub_kls = re.match('dict\((.*), (.*)\)', klass).group(2)
        return {k: self.__deserialize(v, sub_kls) for k, v in iteritems(data)}

      # convert str to class
      # for native types
      if klass in ['int', 'float', 'str', 'bool', 'datetime', "object"]:
        klass = eval(klass)
      # for model types
      else:
        klass = eval('models.' + klass)

    if klass in [int, float, str, bool]:
      return self.__deserialize_primitive(data, klass)
    elif klass == object:
      return self.__deserialize_object()
    elif klass == datetime:
      return self.__deserialize_datatime(data)
    else:
      return self.__deserialize_model(data, klass)

  def request(self, method, url, query_params=None, headers=None, post_params=None, body=None):
    """
    Perform http request using RESTClient.
    """
    if method == "GET":
      return RESTClient.GET(url, query_params=query_params, headers=headers)
    elif method == "HEAD":
      return RESTClient.HEAD(url, query_params=query_params, headers=headers)
    elif method == "POST":
      return RESTClient.POST(url, headers=headers, post_params=post_params, body=body)
    elif method == "PUT":
      return RESTClient.PUT(url, headers=headers, post_params=post_params, body=body)
    elif method == "PATCH":
      return RESTClient.PATCH(url, headers=headers, post_params=post_params, body=body)
    elif method == "DELETE":
      return RESTClient.DELETE(url, query_params=query_params, headers=headers)
    else:
      raise ValueError("http method must be `GET`, `HEAD`, `POST`, `PATCH`, `PUT` or `DELETE`")

  def prepare_post_parameters(self, post_params=None, files=None):
    params = {}

    if post_params:
      params.update(post_params)

    if files:
      for k, v in iteritems(files):
        if v:
          with open(v, 'rb') as f:
            filename = os.path.basename(f.name)
            filedata = f.read()
            mimetype = mimetypes.guess_type(filename)[0] or 'application/octet-stream'
            params[k] = tuple([filename, filedata, mimetype])

    return params

  def select_header_accept(self, accepts):
    """
    Return `Accept` based on an array of accepts provided
    """
    if not accepts:
      return

    accepts = list(map(lambda x: x.lower(), accepts))

    if 'application/json' in accepts:
      return 'application/json'
    else:
      return ', '.join(accepts)

  def select_header_content_type(self, content_types):
    """
    Return `Content-Type` baseed on an array of content_types provided
    """
    if not content_types:
      return 'application/json'

    content_types = list(map(lambda x: x.lower(), content_types))

    if 'application/json' in content_types:
      return 'application/json'
    else:
      return content_types[0]

  def update_params_for_auth(self, headers, querys, auth_settings):
    """
    Update header and query params based on authentication setting
    """
    if not auth_settings:
      return

    for auth in auth_settings:
      auth_setting = configuration.auth_settings().get(auth)
      if auth_setting:
        if auth_setting['in'] == 'header':
          headers[auth_setting['key']] = auth_setting['value']
        elif auth_setting['in'] == 'query':
          querys[auth_setting['key']] = auth_setting['value']
        else:
          raise ValueError('Authentication token must be in `query` or `header`')

  def __deserialize_file(self, response):
    """
    Save response body into a file in (the defined) temporary folder, using the filename
    from the `Content-Disposition` header if provided, otherwise a random filename.

    :param response:  RESTResponse
    :return: file path
    """
    fd, path = tempfile.mkstemp(dir=configuration.temp_folder_path)
    os.close(fd)
    os.remove(path)

    content_disposition = response.getheader("Content-Disposition")
    if content_disposition:
      filename = re.search(r'filename=[\'"]?([^\'"\s]+)[\'"]?', content_disposition).group(1)
      path = os.path.join(os.path.dirname(path), filename)

    with open(path, "w") as f:
      f.write(response.data)

    return path

  def __deserialize_primitive(self, data, klass):
    """
    Deserialize string to primitive type

    :param data: str
    :param klass: class literal

    :return: int, float, str, bool
    """
    try:
      value = klass(data)
    except UnicodeEncodeError:
      value = unicode(data)
    except TypeError:
      value = data
    return value

  def __deserialize_object(self):
    """
    Deserialize empty object
    """
    return object()

  def __deserialize_datatime(self, string):
    """
    Deserialize string to datetime.

    The string should be in iso8601 datetime format.

    :param string: str
    :return: datetime
    """
    try:
      from dateutil.parser import parse
      return parse(string)
    except ImportError:
      return string
    except ValueError:
      raise ApiException(status=0, reason="Failed to parse `{0}` into a datetime object".format(string))

  def __deserialize_model(self, data, klass):
    """
    Deserialize list or dict to model

    :param data: dict, list
    :param klass: class literal
    """
    instance = klass()

    for attr, attr_type in iteritems(instance.swagger_types):
      if data is not None \
         and instance.attribute_map[attr] in data\
         and isinstance(data, (list, dict)):
        value = data[instance.attribute_map[attr]]
        setattr(instance, attr, self.__deserialize(value, attr_type))

    return instance
