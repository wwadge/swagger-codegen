require 'rubygems'
require 'bundler/setup'
require 'swagger-client'
require 'vcr'
require 'typhoeus'
require 'json'
require 'yaml'
require 'rspec'

RSpec.configure do |config|
  # some (optional) config here
  config.expect_with :rspec do |c|
    c.syntax = :should
  end
  config.mock_with :rspec do |c|
    c.syntax = :should
  end
end


WebMock.allow_net_connect! if defined? WebMock

def help
  puts "\nOh noes! You gotta stuff your swagger credentials in ~/.swagger.yml like so:\n\n"
  puts "api_key: '12345abcdefg'"
  puts "username: 'fumanchu'"
  puts "password: 'kalamazoo'\n\n"
  exit
end

# no longer reading credentials (not used) from file (20150413)
# Parse ~/.swagger.yml for user credentials
#begin
#  CREDENTIALS = YAML::load_file(File.join(ENV['HOME'], ".swagger.yml")).symbolize_keys
#rescue
#  help
#end

def configure_swagger
  Swagger.configure do |config|
    config.api_key = 'special-key'
    config.host = 'petstore.swagger.io'
    config.base_path = '/v2'
  end
end

# always delete and then re-create the pet object with 10002
def prepare_pet
  # remove the pet
  PetApi.delete_pet('special-key', 10002)
  # recreate the pet
  pet = Pet.new('id' => 10002, 'name' => "RUBY UNIT TESTING")
  PetApi.add_pet(pet)
end

# always delete and then re-create the store order 
def prepare_store
  order = Order.new("id" => 10002,
		  "petId" => 10002,
		  "quantity" => 789,
		  "shipDate" => "2015-04-06T23:42:01.678Z",
		  "status" => "placed",
		  "complete" => false)
  StoreApi.place_order(order)
end

configure_swagger

# A random string to tack onto stuff to ensure we're not seeing 
# data from a previous test run
RAND = ("a".."z").to_a.sample(8).join
