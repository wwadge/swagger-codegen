#import <Foundation/Foundation.h>
#import "SWGUser.h"
#import "SWGObject.h"
#import "SWGApiClient.h"


@interface SWGUserApi: NSObject

@property(nonatomic, assign)SWGApiClient *apiClient;

-(instancetype) initWithApiClient:(SWGApiClient *)apiClient;
-(void) addHeader:(NSString*)value forKey:(NSString*)key;
-(unsigned long) requestQueueSize;
+(SWGUserApi*) apiWithHeader:(NSString*)headerValue key:(NSString*)key;
+(void) setBasePath:(NSString*)basePath;
+(NSString*) getBasePath;
//
//
// Create user
// This can only be done by the logged in user.
//
// @param body Created user object
// 
//
// @return 
-(NSNumber*) createUserWithCompletionBlock :(SWGUser*) body 
    
    
    completionHandler: (void (^)(NSError* error))completionBlock;


//
//
// Creates list of users with given input array
// 
//
// @param body List of user object
// 
//
// @return 
-(NSNumber*) createUsersWithArrayInputWithCompletionBlock :(NSArray<SWGUser>*) body 
    
    
    completionHandler: (void (^)(NSError* error))completionBlock;


//
//
// Creates list of users with given input array
// 
//
// @param body List of user object
// 
//
// @return 
-(NSNumber*) createUsersWithListInputWithCompletionBlock :(NSArray<SWGUser>*) body 
    
    
    completionHandler: (void (^)(NSError* error))completionBlock;


//
//
// Logs user into the system
// 
//
// @param username The user name for login
// @param password The password for login in clear text
// 
//
// @return NSString*
-(NSNumber*) loginUserWithCompletionBlock :(NSString*) username 
     password:(NSString*) password 
    
    completionHandler: (void (^)(NSString* output, NSError* error))completionBlock;
    


//
//
// Logs out current logged in user session
// 
//
// 
//
// @return 
-(NSNumber*) logoutUserWithCompletionBlock :
    
    (void (^)(NSError* error))completionBlock;


//
//
// Get user by user name
// 
//
// @param username The name that needs to be fetched. Use user1 for testing. 
// 
//
// @return SWGUser*
-(NSNumber*) getUserByNameWithCompletionBlock :(NSString*) username 
    
    completionHandler: (void (^)(SWGUser* output, NSError* error))completionBlock;
    


//
//
// Updated user
// This can only be done by the logged in user.
//
// @param username name that need to be deleted
// @param body Updated user object
// 
//
// @return 
-(NSNumber*) updateUserWithCompletionBlock :(NSString*) username 
     body:(SWGUser*) body 
    
    
    completionHandler: (void (^)(NSError* error))completionBlock;


//
//
// Delete user
// This can only be done by the logged in user.
//
// @param username The name that needs to be deleted
// 
//
// @return 
-(NSNumber*) deleteUserWithCompletionBlock :(NSString*) username 
    
    
    completionHandler: (void (^)(NSError* error))completionBlock;



@end
