#!/usr/bin/env python
"""
UserApi.py
Copyright 2015 Reverb Technologies, Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

NOTE: This class is auto generated by the swagger code generator program. Do not edit the class manually.
"""
import sys
import os

from .models import *


class UserApi(object):

    def __init__(self, apiClient):
      self.apiClient = apiClient

    
    
    def createUser(self, **kwargs):
        """Create user

        Args:
            
            body, User: Created user object (required)
            
            
        
        Returns: 
        """

        allParams = ['body']

        params = locals()
        for (key, val) in params['kwargs'].items():
            if key not in allParams:
                raise TypeError("Got an unexpected keyword argument '%s' to method createUser" % key)
            params[key] = val
        del params['kwargs']

        resourcePath = '/user'
        resourcePath = resourcePath.replace('{format}', 'json')
        method = 'POST'

        queryParams = {}
        headerParams = {}

        

        

        

        postData = (params['body'] if 'body' in params else None)

        response = self.apiClient.callAPI(resourcePath, method, queryParams,
                                          postData, headerParams)

        
        
        
    
    def createUsersWithArrayInput(self, **kwargs):
        """Creates list of users with given input array

        Args:
            
            body, list[User]: List of user object (required)
            
            
        
        Returns: 
        """

        allParams = ['body']

        params = locals()
        for (key, val) in params['kwargs'].items():
            if key not in allParams:
                raise TypeError("Got an unexpected keyword argument '%s' to method createUsersWithArrayInput" % key)
            params[key] = val
        del params['kwargs']

        resourcePath = '/user/createWithArray'
        resourcePath = resourcePath.replace('{format}', 'json')
        method = 'POST'

        queryParams = {}
        headerParams = {}

        

        

        

        postData = (params['body'] if 'body' in params else None)

        response = self.apiClient.callAPI(resourcePath, method, queryParams,
                                          postData, headerParams)

        
        
        
    
    def createUsersWithListInput(self, **kwargs):
        """Creates list of users with given input array

        Args:
            
            body, list[User]: List of user object (required)
            
            
        
        Returns: 
        """

        allParams = ['body']

        params = locals()
        for (key, val) in params['kwargs'].items():
            if key not in allParams:
                raise TypeError("Got an unexpected keyword argument '%s' to method createUsersWithListInput" % key)
            params[key] = val
        del params['kwargs']

        resourcePath = '/user/createWithList'
        resourcePath = resourcePath.replace('{format}', 'json')
        method = 'POST'

        queryParams = {}
        headerParams = {}

        

        

        

        postData = (params['body'] if 'body' in params else None)

        response = self.apiClient.callAPI(resourcePath, method, queryParams,
                                          postData, headerParams)

        
        
        
    
    def loginUser(self, **kwargs):
        """Logs user into the system

        Args:
            
            username, str: The user name for login (required)
            
            
            password, str: The password for login in clear text (required)
            
            
        
        Returns: str
        """

        allParams = ['username', 'password']

        params = locals()
        for (key, val) in params['kwargs'].items():
            if key not in allParams:
                raise TypeError("Got an unexpected keyword argument '%s' to method loginUser" % key)
            params[key] = val
        del params['kwargs']

        resourcePath = '/user/login'
        resourcePath = resourcePath.replace('{format}', 'json')
        method = 'GET'

        queryParams = {}
        headerParams = {}

        
        if ('username' in params):
            queryParams['username'] = self.apiClient.toPathValue(params['username'])
        
        if ('password' in params):
            queryParams['password'] = self.apiClient.toPathValue(params['password'])
        

        

        

        postData = (params['body'] if 'body' in params else None)

        response = self.apiClient.callAPI(resourcePath, method, queryParams,
                                          postData, headerParams)

        
        if not response:
            return None

        responseObject = self.apiClient.deserialize(response, 'str')
        return responseObject
        
        
        
    
    def logoutUser(self, **kwargs):
        """Logs out current logged in user session

        Args:
            
        
        Returns: 
        """

        allParams = []

        params = locals()
        for (key, val) in params['kwargs'].items():
            if key not in allParams:
                raise TypeError("Got an unexpected keyword argument '%s' to method logoutUser" % key)
            params[key] = val
        del params['kwargs']

        resourcePath = '/user/logout'
        resourcePath = resourcePath.replace('{format}', 'json')
        method = 'GET'

        queryParams = {}
        headerParams = {}

        

        

        

        postData = (params['body'] if 'body' in params else None)

        response = self.apiClient.callAPI(resourcePath, method, queryParams,
                                          postData, headerParams)

        
        
        
    
    def getUserByName(self, **kwargs):
        """Get user by user name

        Args:
            
            username, str: The name that needs to be fetched. Use user1 for testing.  (required)
            
            
        
        Returns: User
        """

        allParams = ['username']

        params = locals()
        for (key, val) in params['kwargs'].items():
            if key not in allParams:
                raise TypeError("Got an unexpected keyword argument '%s' to method getUserByName" % key)
            params[key] = val
        del params['kwargs']

        resourcePath = '/user/{username}'
        resourcePath = resourcePath.replace('{format}', 'json')
        method = 'GET'

        queryParams = {}
        headerParams = {}

        

        

        
        if ('username' in params):
            replacement = str(self.apiClient.toPathValue(params['username']))
            resourcePath = resourcePath.replace('{' + 'username' + '}',
                                                replacement)
        

        postData = (params['body'] if 'body' in params else None)

        response = self.apiClient.callAPI(resourcePath, method, queryParams,
                                          postData, headerParams)

        
        if not response:
            return None

        responseObject = self.apiClient.deserialize(response, 'User')
        return responseObject
        
        
        
    
    def updateUser(self, **kwargs):
        """Updated user

        Args:
            
            username, str: name that need to be deleted (required)
            
            
            body, User: Updated user object (required)
            
            
        
        Returns: 
        """

        allParams = ['username', 'body']

        params = locals()
        for (key, val) in params['kwargs'].items():
            if key not in allParams:
                raise TypeError("Got an unexpected keyword argument '%s' to method updateUser" % key)
            params[key] = val
        del params['kwargs']

        resourcePath = '/user/{username}'
        resourcePath = resourcePath.replace('{format}', 'json')
        method = 'PUT'

        queryParams = {}
        headerParams = {}

        

        

        
        if ('username' in params):
            replacement = str(self.apiClient.toPathValue(params['username']))
            resourcePath = resourcePath.replace('{' + 'username' + '}',
                                                replacement)
        

        postData = (params['body'] if 'body' in params else None)

        response = self.apiClient.callAPI(resourcePath, method, queryParams,
                                          postData, headerParams)

        
        
        
    
    def deleteUser(self, **kwargs):
        """Delete user

        Args:
            
            username, str: The name that needs to be deleted (required)
            
            
        
        Returns: 
        """

        allParams = ['username']

        params = locals()
        for (key, val) in params['kwargs'].items():
            if key not in allParams:
                raise TypeError("Got an unexpected keyword argument '%s' to method deleteUser" % key)
            params[key] = val
        del params['kwargs']

        resourcePath = '/user/{username}'
        resourcePath = resourcePath.replace('{format}', 'json')
        method = 'DELETE'

        queryParams = {}
        headerParams = {}

        

        

        
        if ('username' in params):
            replacement = str(self.apiClient.toPathValue(params['username']))
            resourcePath = resourcePath.replace('{' + 'username' + '}',
                                                replacement)
        

        postData = (params['body'] if 'body' in params else None)

        response = self.apiClient.callAPI(resourcePath, method, queryParams,
                                          postData, headerParams)

        
        
        
    


