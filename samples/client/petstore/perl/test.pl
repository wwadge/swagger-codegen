#!/usr/bin/perl
#
#
use lib 'lib';
use strict;
use warnings;
use WWW::SwaggerClient::PetApi;
use WWW::SwaggerClient::APIClient;
use WWW::SwaggerClient::Object::Pet;
use WWW::SwaggerClient::Object::Tag;
use WWW::SwaggerClient::Object::Category;
use JSON;
use Data::Dumper;
use DateTime;

my $api = WWW::SwaggerClient::PetApi->new();

my $pet_id = 88;

my $category =  WWW::SwaggerClient::Object::Category->new('id' => '2', 'name' => 'perl');
my $tag =  WWW::SwaggerClient::Object::Tag->new('id' => '1', 'name' => 'just kidding'); 
my $pet =  WWW::SwaggerClient::Object::Pet->new('id' => $pet_id, 'name' => 'perl test', 
    "photoUrls" => ['123', 'oop'], 'tags' => [$tag], 'status' => 'pending', 'category' => $category);

print "\npet(object)=".Dumper $pet;
my $json = JSON->new->convert_blessed;

my $new_pet = WWW::SwaggerClient::Object::Pet->new();
$new_pet = $new_pet->from_hash($pet->to_hash);
print "new_pet(hash):".Dumper($new_pet->to_hash);

print "\nTest Petstore endpoints\n";
print "\nupload_file:".Dumper $api->upload_file(pet_id => $pet_id, additional_metadata => 'testabc', file => '/var/tmp/f5.jpg');
print "\nadd_pet:".Dumper $api->add_pet(body => $pet);
print "\nget_pet_by_id:".Dumper $api->get_pet_by_id(pet_id => $pet_id);
print "\nupdate_pet_with_form:".Dumper $api->update_pet_with_form(pet_id => $pet_id, name => 'test_name', status => 'test status');
print "\ndelete_pet:".Dumper $api->delete_pet(pet_id => $pet_id);




