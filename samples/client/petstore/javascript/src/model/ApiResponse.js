(function(root, factory) {
  if (typeof define === 'function' && define.amd) {
    // AMD. Register as an anonymous module.
    define(['ApiClient'], factory);
  } else if (typeof module === 'object' && module.exports) {
    // CommonJS-like environments that support module.exports, like Node.
    module.exports = factory(require('../ApiClient'));
  } else {
    // Browser globals (root is window)
    if (!root.SwaggerPetstore) {
      root.SwaggerPetstore = {};
    }
    root.SwaggerPetstore.ApiResponse = factory(root.SwaggerPetstore.ApiClient);
  }
}(this, function(ApiClient) {
  'use strict';

  /**
   * The ApiResponse model module.
   * @module model/ApiResponse
   * @version 1.0.0
   */

  /**
   * Constructs a new <code>ApiResponse</code>.
   * @alias module:model/ApiResponse
   * @class
   */
  var exports = function() {
    var _this = this;




  };

  /**
   * Constructs a <code>ApiResponse</code> from a plain JavaScript object, optionally creating a new instance.
   * Copies all relevant properties from <code>data</code> to <code>obj</code> if supplied or a new instance if not.
   * @param {Object} data The plain JavaScript object bearing properties of interest.
   * @param {module:model/ApiResponse} obj Optional instance to populate.
   * @return {module:model/ApiResponse} The populated <code>ApiResponse</code> instance.
   */
  exports.constructFromObject = function(data, obj) {
    if (data) {
      obj = obj || new exports();

      if (data.hasOwnProperty('code')) {
        obj['code'] = ApiClient.convertToType(data['code'], 'Integer');
      }
      if (data.hasOwnProperty('type')) {
        obj['type'] = ApiClient.convertToType(data['type'], 'String');
      }
      if (data.hasOwnProperty('message')) {
        obj['message'] = ApiClient.convertToType(data['message'], 'String');
      }
    }
    return obj;
  }


  /**
   * @member {Integer} code
   */
  exports.prototype['code'] = undefined;

  /**
   * @member {String} type
   */
  exports.prototype['type'] = undefined;

  /**
   * @member {String} message
   */
  exports.prototype['message'] = undefined;




  return exports;
}));
