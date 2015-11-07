package WWW::SwaggerClient::Role;
use utf8;

use Moose::Role;
use namespace::autoclean;
use Class::Inspector;

use WWW::SwaggerClient::ApiFactory;

requires 'auth_setup_handler';

has base_url => ( is => 'ro',
			 	  required => 0,
			 	  isa => 'Str',
			 	  );

has api_factory => ( is => 'ro',
					 isa => 'WWW::SwaggerClient::ApiFactory',
					 builder => '_build_af', 
					 lazy => 1,
					 );
					 
sub BUILD {
	my $self = shift;
	
	my %outsiders = map {$_ => 1} qw( croak );
	
	foreach my $name ($self->api_factory->apis_available) {
		
		my $att_name = sprintf "%s_api", lc($name);
		my $api_class = $self->api_factory->classname_for($name);
		my $methods = Class::Inspector->methods($api_class, 'expanded');
		my @local_methods = grep {! $outsiders{$_}} map {$_->[2]} grep {$_->[1] eq $api_class} @$methods;
		
		$self->meta->add_attribute( $att_name => ( 
									is => 'ro',
									isa => $api_class,
									default => sub {$self->api_factory->get_api($name)},
									lazy => 1,
									handles => \@local_methods,
									) );
	}
}

sub _build_af {
	my $self = shift;
	my %args = ( auth_setup_handler_object => $self );
	$args{base_url} = $self->base_url if $self->base_url;
	return WWW::SwaggerClient::ApiFactory->new(%args);
}



1;
