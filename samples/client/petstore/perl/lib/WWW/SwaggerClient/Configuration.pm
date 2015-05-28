package WWW::SwaggerClient::Configuration;

use strict;
use warnings;
use utf8;

use Log::Any qw($log);
use Carp;

# class/static variables
our $api_client;
our $http_timeout = 180;
our $http_user_agent = 'Perl-Swagger';


1;
