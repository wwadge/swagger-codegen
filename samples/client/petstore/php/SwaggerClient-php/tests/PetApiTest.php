<?php

require_once('SwaggerClient.php');

class PetApiTest extends \PHPUnit_Framework_TestCase
{

  // add a new pet (id 10005) to ensure the pet object is available for all the tests
  public static function setUpBeforeClass() {
    // initialize the API client
    $api_client = new SwaggerClient\APIClient('http://petstore.swagger.io/v2');
    $new_pet_id = 10005;
    $new_pet = new SwaggerClient\models\Pet;
    $new_pet->id = $new_pet_id;
    $new_pet->name = "PHP Unit Test";
    $pet_api = new SwaggerClient\PetAPI($api_client);
    // add a new pet (model)
    $add_response = $pet_api->addPet($new_pet);
    // return nothing (void)
    //$this->assertSame($add_response, NULL);
  }

  // test getPetById with a Pet object (id 10005)
  public function testGetPetById()
  {
    // initialize the API client
    $api_client = new SwaggerClient\APIClient('http://petstore.swagger.io/v2');
    $pet_id = 10005;  // ID of pet that needs to be fetched
    $pet_api = new SwaggerClient\PetAPI($api_client);
    // return Pet (model)
    $response = $pet_api->getPetById($pet_id);
    $this->assertSame($response->id, $pet_id);
    $this->assertSame($response->name, 'PHP Unit Test');
  }

  // test getPetByStatus and verify by the "id" of the response
  public function testFindPetByStatus()
  {
    // initialize the API client
    $api_client = new SwaggerClient\APIClient('http://petstore.swagger.io/v2');
    $pet_api = new SwaggerClient\PetAPI($api_client);
    // return Pet (model)
    $response = $pet_api->findPetsByStatus("available");
    $this->assertGreaterThan(0, count($response)); // at least one object returned
    $this->assertSame(get_class($response[0]), "SwaggerClient\models\Pet"); // verify the object is Pet
    // loop through result to ensure status is "available" 
    foreach ($response as $_pet) {
      $this->assertSame($_pet['status'], "available");
    }
    // test invalid status 
    $response = $pet_api->findPetsByStatus("unknown_and_incorrect_status");
    $this->assertSame(count($response), 0); // confirm no object returned
  }

  // test updatePet (model/json)and verify by the "id" of the response
  public function testUpdatePet()
  {
    // initialize the API client
    $api_client = new SwaggerClient\APIClient('http://petstore.swagger.io/v2');
    $pet_id = 10001;  // ID of pet that needs to be fetched
    $pet_api = new SwaggerClient\PetAPI($api_client);
    // create updated pet object
    $updated_pet = new SwaggerClient\models\Pet;
    $updated_pet->id = $pet_id;
    $updated_pet->status = "pending"; // new status
    // update Pet (model/json)
    $update_response = $pet_api->updatePet($updated_pet);
    // return nothing (void)
    $this->assertSame($update_response, NULL);
    // verify updated Pet
    $response = $pet_api->getPetById($pet_id);
    $this->assertSame($response->id, $pet_id);
    $this->assertSame($response->status, 'pending');
  }

  // test updatePet and verify by the "id" of the response
  public function testUpdatePetWithForm()
  {
    // initialize the API client
    $api_client = new SwaggerClient\APIClient('http://petstore.swagger.io/v2');
    $pet_id = 10001;  // ID of pet that needs to be fetched
    $pet_api = new SwaggerClient\PetAPI($api_client);
    // update Pet (form)
    $update_response = $pet_api->updatePetWithForm($pet_id, null, 'sold');
    // return nothing (void)
    $this->assertSame($update_response, NULL);
    // TODO commented out for the time being since it's broken
    // https://github.com/swagger-api/swagger-codegen/issues/656
    // verify updated Pet
    //$response = $pet_api->getPetById($pet_id);
    //$this->assertSame($response->id, $pet_id);
    //$this->assertSame($response->status, 'sold');
  }

  // test addPet and verify by the "id" and "name" of the response
  public function testAddPet()
  {
    // initialize the API client
    $api_client = new SwaggerClient\APIClient('http://petstore.swagger.io/v2');
    $new_pet_id = 10001;
    $new_pet = new SwaggerClient\models\Pet;
    $new_pet->id = $new_pet_id;
    $new_pet->name = "PHP Unit Test";
    $pet_api = new SwaggerClient\PetAPI($api_client);
    // add a new pet (model)
    $add_response = $pet_api->addPet($new_pet);
    // return nothing (void)
    $this->assertSame($add_response, NULL);
    // verify added Pet
    $response = $pet_api->getPetById($new_pet_id);
    $this->assertSame($response->id, $new_pet_id);
    $this->assertSame($response->name, 'PHP Unit Test');
  }

}

?>

