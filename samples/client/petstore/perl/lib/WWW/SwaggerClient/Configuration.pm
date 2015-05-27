package WWW::SwaggerClient::Configuration;

use strict;
use warnings;
use utf8;

use Log::Any qw($log);
use Carp;

# class/static variables
my $api_client = WWW::SwaggerClient::APIClient->new;
my $http_timeout = 180;
my $http_user_agent = 'Perl-Swagger';


1;
