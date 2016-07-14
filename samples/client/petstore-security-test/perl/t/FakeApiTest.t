=begin comment

Swagger Petstore  ' \" =end

This spec is mainly for testing Petstore server and contains fake endpoints, models. Please do not use this for any other purpose. Special characters: \" \\   ' \" =end

OpenAPI spec version: 1.0.0  &#39; \&quot; &#x3D;end
Contact: apiteam@swagger.io  ' \" =end
Generated by: https://github.com/swagger-api/swagger-codegen.git

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

=end comment

=cut

#
# NOTE: This class is auto generated by Swagger Codegen
# Please update the test cases below to test the API endpoints.
# Ref: https://github.com/swagger-api/swagger-codegen
#
use Test::More tests => 1; #TODO update number of test cases
use Test::Exception;

use lib 'lib';
use strict;
use warnings;

use_ok('WWW::SwaggerClient::FakeApi');

my $api = WWW::SwaggerClient::FakeApi->new();
isa_ok($api, 'WWW::SwaggerClient::FakeApi');

#
# test_code_inject */ ' " =end test
#
{
    my $test code inject */ &#39; &quot; &#x3D;end = undef; # replace NULL with a proper value
    my $result = $api->test_code_inject */ &#39; &quot; &#x3D;end(test code inject */ &#39; &quot; &#x3D;end => $test code inject */ &#39; &quot; &#x3D;end);
}


1;
