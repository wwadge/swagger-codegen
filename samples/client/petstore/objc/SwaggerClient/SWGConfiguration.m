#import "SWGConfiguration.h"

@interface SWGConfiguration ()

@property (readwrite, nonatomic, strong) NSMutableDictionary *mutableApiKey;
@property (readwrite, nonatomic, strong) NSMutableDictionary *mutableApiKeyPrefix;

@end

@implementation SWGConfiguration

#pragma mark - Singletion Methods

+ (instancetype) sharedConfig {
    static SWGConfiguration *shardConfig = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        shardConfig = [[self alloc] init];
    });
    return shardConfig;
}

#pragma mark - Initialize Methods

- (instancetype) init {
    self = [super init];
    if (self) {
        self.username = @"";
        self.password = @"";
        self.tempFolderPath = nil;
        self.debug = NO;
        self.loggingFile = nil;
        self.mutableApiKey = [NSMutableDictionary dictionary];
        self.mutableApiKeyPrefix = [NSMutableDictionary dictionary];
    }
    return self;
}

#pragma mark - Instance Methods

- (NSString *) getApiKeyWithPrefix:(NSString *)key {
    if ([self.apiKeyPrefix objectForKey:key] && [self.apiKey objectForKey:key]) {
        return [NSString stringWithFormat:@"%@ %@", [self.apiKeyPrefix objectForKey:key], [self.apiKey objectForKey:key]];
    }
    else if ([self.apiKey objectForKey:key]) {
        return [NSString stringWithFormat:@"%@", [self.apiKey objectForKey:key]];
    }
    else {
        return @"";
    }
}

- (NSString *) getBasicAuthToken {
    NSString *basicAuthCredentials = [NSString stringWithFormat:@"%@:%@", self.username, self.password];
    NSData *data = [basicAuthCredentials dataUsingEncoding:NSUTF8StringEncoding];
    basicAuthCredentials = [NSString stringWithFormat:@"Basic %@", [data base64EncodedStringWithOptions:0]];
    
    return basicAuthCredentials;
}

#pragma mark - Setter Methods

- (void) setValue:(NSString *)value forApiKeyField:(NSString *)field {
    [self.mutableApiKey setValue:value forKey:field];
}

- (void) setValue:(NSString *)value forApiKeyPrefixField:(NSString *)field {
    [self.mutableApiKeyPrefix setValue:value forKey:field];
}

- (void) setLoggingFile:(NSString *)loggingFile {
    // close old file handler
    if ([self.loggingFileHanlder isKindOfClass:[NSFileHandle class]]) {
        [self.loggingFileHanlder closeFile];
    }
    
    _loggingFile = loggingFile;
    self.loggingFileHanlder = [NSFileHandle fileHandleForWritingAtPath:_loggingFile];
    if (self.loggingFileHanlder == nil) {
        [[NSFileManager defaultManager] createFileAtPath:_loggingFile contents:nil attributes:nil];
        self.loggingFileHanlder = [NSFileHandle fileHandleForWritingAtPath:_loggingFile];
    }
}

#pragma mark - Getter Methods

- (NSDictionary *) apiKey {
    return [NSDictionary dictionaryWithDictionary:self.mutableApiKey];
}

- (NSDictionary *) apiKeyPrefix {
    return [NSDictionary dictionaryWithDictionary:self.mutableApiKeyPrefix];
}

#pragma mark -

- (NSDictionary *) authSettings {
    return @{ 
                @"api_key": @{
                    @"type": @"api_key",
                    @"in": @"header",
                    @"key": @"api_key",
                    @"value": [self getApiKeyWithPrefix:@"api_key"]
                },
              
            };
}

@end
