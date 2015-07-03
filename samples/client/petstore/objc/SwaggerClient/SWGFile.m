#import "SWGFile.h"

@implementation SWGFile

- (id) init {
    self = [super init];
    return self;
}

- (id) initWithNameData: (NSString*) filename
               mimeType: (NSString*) fileMimeType
                   data: (NSData*) data {
	self = [super init];
	if(self) {
		_name = filename;
		_mimeType = fileMimeType;
		_data = data;
	}
	return self;
}

- (id) initWithPath:(NSString *)filepath data:(NSData *)data name:(NSString *)filename {
    self = [super init];
    
    if (self) {
        _name = filename;
        _data = data;
        _path = filepath;
        [data writeToFile:_path atomically:YES];
    }
    
    return self;
}

@end
