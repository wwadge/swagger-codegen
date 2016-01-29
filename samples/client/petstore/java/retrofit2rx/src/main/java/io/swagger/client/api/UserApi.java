package io.swagger.client.api;

import io.swagger.client.CollectionFormats.*;

import rx.Observable;

import retrofit.http.*;

import com.squareup.okhttp.RequestBody;

import io.swagger.client.model.User;
import java.util.*;

import java.util.*;

public interface UserApi {
  
  /**
   * Create user
   * This can only be done by the logged in user.
   * @param body Created user object
   * @return Call<Void>
   */
  
  @POST("user")
  Observable<Void> createUser(
    @Body User body
  );

  
  /**
   * Creates list of users with given input array
   * 
   * @param body List of user object
   * @return Call<Void>
   */
  
  @POST("user/createWithArray")
  Observable<Void> createUsersWithArrayInput(
    @Body List<User> body
  );

  
  /**
   * Creates list of users with given input array
   * 
   * @param body List of user object
   * @return Call<Void>
   */
  
  @POST("user/createWithList")
  Observable<Void> createUsersWithListInput(
    @Body List<User> body
  );

  
  /**
   * Logs user into the system
   * 
   * @param username The user name for login
   * @param password The password for login in clear text
   * @return Call<String>
   */
  
  @GET("user/login")
  Observable<String> loginUser(
    @Query("username") String username, @Query("password") String password
  );

  
  /**
   * Logs out current logged in user session
   * 
   * @return Call<Void>
   */
  
  @GET("user/logout")
  Observable<Void> logoutUser();
    

  
  /**
   * Get user by user name
   * 
   * @param username The name that needs to be fetched. Use user1 for testing.
   * @return Call<User>
   */
  
  @GET("user/{username}")
  Observable<User> getUserByName(
    @Path("username") String username
  );

  
  /**
   * Updated user
   * This can only be done by the logged in user.
   * @param username name that need to be deleted
   * @param body Updated user object
   * @return Call<Void>
   */
  
  @PUT("user/{username}")
  Observable<Void> updateUser(
    @Path("username") String username, @Body User body
  );

  
  /**
   * Delete user
   * This can only be done by the logged in user.
   * @param username The name that needs to be deleted
   * @return Call<Void>
   */
  
  @DELETE("user/{username}")
  Observable<Void> deleteUser(
    @Path("username") String username
  );

  
}
