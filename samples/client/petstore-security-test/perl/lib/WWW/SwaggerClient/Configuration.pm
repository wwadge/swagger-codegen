=begin comment

Swagger Petstore */ ' \" 

This spec is mainly for testing Petstore server and contains fake endpoints, models. Please do not use this for any other purpose. Special characters: \" \\  */ ' \" 

OpenAPI spec version: 1.0.0 */ &#39; \&quot; 
Contact: apiteam@swagger.io */ ' \" 
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
# NOTE: This class is auto generated by the swagger code generator program. 
# Do not edit the class manually.
# Ref: https://github.com/swagger-api/swagger-codegen
#
package WWW::SwaggerClient::Configuration;

use strict;
use warnings;
use utf8;

use Log::Any qw($log);
use Carp;

use constant VERSION => '1.0.0';

# class/static variables
our $http_timeout = 180;
our $http_user_agent = 'Perl-Swagger';

# authenticaiton setting
our $api_key = {};
our $api_key_prefix = {};
our $api_key_in = {};

# username and password for HTTP basic authentication
our $username = '';
our $password = '';

# access token for OAuth
our $access_token = '';

sub get_tokens {
	my $class = shift;
	
	my $tokens = {};
	$tokens->{username} = $username if $username;
	$tokens->{password} = $password if $password;
	$tokens->{access_token} = $access_token if $access_token;
	
	foreach my $token_name (keys %{ $api_key }) {
		$tokens->{$token_name}->{token} = $api_key->{$token_name};
		$tokens->{$token_name}->{prefix} = $api_key_prefix->{$token_name};
		$tokens->{$token_name}->{in} = $api_key_in->{$token_name};
	}

	return $tokens;
}

sub clear_tokens {
	my $class = shift;
	my %tokens = %{$class->get_tokens}; # copy
	
	$username = undef;
	$password = undef;
	$access_token = undef;

	$api_key = {};
	$api_key_prefix = {};
	$api_key_in = {};
	
	return \%tokens;
}

sub accept_tokens {
	my ($class, $tokens) = @_;
	
	foreach my $known_name (qw(username password access_token)) {
		next unless $tokens->{$known_name};
		eval "\$$known_name = delete \$tokens->{\$known_name}";
		die $@ if $@;
	}
	
	foreach my $token_name (keys %$tokens) {
		$api_key->{$token_name} = $tokens->{$token_name}->{token};
		if ($tokens->{$token_name}->{prefix}) {
			$api_key_prefix->{$token_name} = $tokens->{$token_name}->{prefix};
		}
		my $in = $tokens->{$token_name}->{in} || 'head';
		croak "Tokens can only go in 'head' or 'query' (not in '$in')" unless $in =~ /^(?:head|query)$/;
		$api_key_in->{$token_name} = $in;
	}
}	

1;
