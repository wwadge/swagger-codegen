/**
 * Swagger Petstore
 * This is a sample server Petstore server.  You can find out more about Swagger at <a href=\"http://swagger.io\">http://swagger.io</a> or on irc.freenode.net, #swagger.  For this sample, you can use the api key \"special-key\" to test the authorization filters
 *
 * OpenAPI spec version: 1.0.0
 * Contact: apiteam@wordnik.com
 *
 * NOTE: This class is auto generated by the swagger code generator program.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path="api.d.ts" />

/* tslint:disable:no-unused-variable member-ordering */

namespace API.Client {
    'use strict';

    export class PetApi {
        protected basePath = 'http://petstore.swagger.io/v2';
        public defaultHeaders : any = {};

        static $inject: string[] = ['$http', '$httpParamSerializer', 'basePath'];

        constructor(protected $http: ng.IHttpService, protected $httpParamSerializer?: (d: any) => any, basePath?: string) {
            if (basePath !== undefined) {
                this.basePath = basePath;
            }
        }

        private extendObj<T1,T2>(objA: T1, objB: T2) {
            for(let key in objB){
                if(objB.hasOwnProperty(key)){
                    objA[key] = objB[key];
                }
            }
            return <T1&T2>objA;
        }

        /**
         * Add a new pet to the store
         * 
         * @param body Pet object that needs to be added to the store
         */
        public addPet (body?: Pet, extraHttpRequestParams?: any ) : ng.IHttpPromise<{}> {
            const localVarPath = this.basePath + '/pet';

            let queryParameters: any = {};
            let headerParams: any = this.extendObj({}, this.defaultHeaders);
            let httpRequestParams: any = {
                method: 'POST',
                url: localVarPath,
                json: true,
                data: body,
                                params: queryParameters,
                headers: headerParams
            };

            if (extraHttpRequestParams) {
                httpRequestParams = this.extendObj(httpRequestParams, extraHttpRequestParams);
            }

            return this.$http(httpRequestParams);
        }
        /**
         * Deletes a pet
         * 
         * @param petId Pet id to delete
         * @param apiKey 
         */
        public deletePet (petId: number, apiKey?: string, extraHttpRequestParams?: any ) : ng.IHttpPromise<{}> {
            const localVarPath = this.basePath + '/pet/{petId}'
                .replace('{' + 'petId' + '}', String(petId));

            let queryParameters: any = {};
            let headerParams: any = this.extendObj({}, this.defaultHeaders);
            // verify required parameter 'petId' is not null or undefined
            if (petId === null || petId === undefined) {
                throw new Error('Required parameter petId was null or undefined when calling deletePet.');
            }
            headerParams['api_key'] = apiKey;

            let httpRequestParams: any = {
                method: 'DELETE',
                url: localVarPath,
                json: true,
                                                params: queryParameters,
                headers: headerParams
            };

            if (extraHttpRequestParams) {
                httpRequestParams = this.extendObj(httpRequestParams, extraHttpRequestParams);
            }

            return this.$http(httpRequestParams);
        }
        /**
         * Finds Pets by status
         * Multiple status values can be provided with comma seperated strings
         * @param status Status values that need to be considered for filter
         */
        public findPetsByStatus (status?: Array<string>, extraHttpRequestParams?: any ) : ng.IHttpPromise<Array<Pet>> {
            const localVarPath = this.basePath + '/pet/findByStatus';

            let queryParameters: any = {};
            let headerParams: any = this.extendObj({}, this.defaultHeaders);
            if (status !== undefined) {
                queryParameters['status'] = status;
            }

            let httpRequestParams: any = {
                method: 'GET',
                url: localVarPath,
                json: true,
                                                params: queryParameters,
                headers: headerParams
            };

            if (extraHttpRequestParams) {
                httpRequestParams = this.extendObj(httpRequestParams, extraHttpRequestParams);
            }

            return this.$http(httpRequestParams);
        }
        /**
         * Finds Pets by tags
         * Muliple tags can be provided with comma seperated strings. Use tag1, tag2, tag3 for testing.
         * @param tags Tags to filter by
         */
        public findPetsByTags (tags?: Array<string>, extraHttpRequestParams?: any ) : ng.IHttpPromise<Array<Pet>> {
            const localVarPath = this.basePath + '/pet/findByTags';

            let queryParameters: any = {};
            let headerParams: any = this.extendObj({}, this.defaultHeaders);
            if (tags !== undefined) {
                queryParameters['tags'] = tags;
            }

            let httpRequestParams: any = {
                method: 'GET',
                url: localVarPath,
                json: true,
                                                params: queryParameters,
                headers: headerParams
            };

            if (extraHttpRequestParams) {
                httpRequestParams = this.extendObj(httpRequestParams, extraHttpRequestParams);
            }

            return this.$http(httpRequestParams);
        }
        /**
         * Find pet by ID
         * Returns a pet when ID &lt; 10.  ID &gt; 10 or nonintegers will simulate API error conditions
         * @param petId ID of pet that needs to be fetched
         */
        public getPetById (petId: number, extraHttpRequestParams?: any ) : ng.IHttpPromise<Pet> {
            const localVarPath = this.basePath + '/pet/{petId}'
                .replace('{' + 'petId' + '}', String(petId));

            let queryParameters: any = {};
            let headerParams: any = this.extendObj({}, this.defaultHeaders);
            // verify required parameter 'petId' is not null or undefined
            if (petId === null || petId === undefined) {
                throw new Error('Required parameter petId was null or undefined when calling getPetById.');
            }
            let httpRequestParams: any = {
                method: 'GET',
                url: localVarPath,
                json: true,
                                                params: queryParameters,
                headers: headerParams
            };

            if (extraHttpRequestParams) {
                httpRequestParams = this.extendObj(httpRequestParams, extraHttpRequestParams);
            }

            return this.$http(httpRequestParams);
        }
        /**
         * Update an existing pet
         * 
         * @param body Pet object that needs to be added to the store
         */
        public updatePet (body?: Pet, extraHttpRequestParams?: any ) : ng.IHttpPromise<{}> {
            const localVarPath = this.basePath + '/pet';

            let queryParameters: any = {};
            let headerParams: any = this.extendObj({}, this.defaultHeaders);
            let httpRequestParams: any = {
                method: 'PUT',
                url: localVarPath,
                json: true,
                data: body,
                                params: queryParameters,
                headers: headerParams
            };

            if (extraHttpRequestParams) {
                httpRequestParams = this.extendObj(httpRequestParams, extraHttpRequestParams);
            }

            return this.$http(httpRequestParams);
        }
        /**
         * Updates a pet in the store with form data
         * 
         * @param petId ID of pet that needs to be updated
         * @param name Updated name of the pet
         * @param status Updated status of the pet
         */
        public updatePetWithForm (petId: string, name?: string, status?: string, extraHttpRequestParams?: any ) : ng.IHttpPromise<{}> {
            const localVarPath = this.basePath + '/pet/{petId}'
                .replace('{' + 'petId' + '}', String(petId));

            let queryParameters: any = {};
            let headerParams: any = this.extendObj({}, this.defaultHeaders);
            let formParams: any = {};

            // verify required parameter 'petId' is not null or undefined
            if (petId === null || petId === undefined) {
                throw new Error('Required parameter petId was null or undefined when calling updatePetWithForm.');
            }
            headerParams['Content-Type'] = 'application/x-www-form-urlencoded';

            formParams['name'] = name;

            formParams['status'] = status;

            let httpRequestParams: any = {
                method: 'POST',
                url: localVarPath,
                json: false,
                                data: this.$httpParamSerializer(formParams),
                params: queryParameters,
                headers: headerParams
            };

            if (extraHttpRequestParams) {
                httpRequestParams = this.extendObj(httpRequestParams, extraHttpRequestParams);
            }

            return this.$http(httpRequestParams);
        }
        /**
         * uploads an image
         * 
         * @param petId ID of pet to update
         * @param additionalMetadata Additional data to pass to server
         * @param file file to upload
         */
        public uploadFile (petId: number, additionalMetadata?: string, file?: any, extraHttpRequestParams?: any ) : ng.IHttpPromise<{}> {
            const localVarPath = this.basePath + '/pet/{petId}/uploadImage'
                .replace('{' + 'petId' + '}', String(petId));

            let queryParameters: any = {};
            let headerParams: any = this.extendObj({}, this.defaultHeaders);
            let formParams: any = {};

            // verify required parameter 'petId' is not null or undefined
            if (petId === null || petId === undefined) {
                throw new Error('Required parameter petId was null or undefined when calling uploadFile.');
            }
            headerParams['Content-Type'] = 'application/x-www-form-urlencoded';

            formParams['additionalMetadata'] = additionalMetadata;

            formParams['file'] = file;

            let httpRequestParams: any = {
                method: 'POST',
                url: localVarPath,
                json: false,
                                data: this.$httpParamSerializer(formParams),
                params: queryParameters,
                headers: headerParams
            };

            if (extraHttpRequestParams) {
                httpRequestParams = this.extendObj(httpRequestParams, extraHttpRequestParams);
            }

            return this.$http(httpRequestParams);
        }
    }
}
