//
//  SDBCoder.h
//  SimpleDB
//
//  Created by OYOL on 2019/6/20.
//  Copyright © 2019 feng. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SDBCoder;

@protocol SDBCoding <NSObject>

- (void)encodeWithSDBCoder:(SDBCoder * _Nonnull)coder;
- (nullable instancetype)initWithSDBCoder:(SDBCoder * _Nonnull)decoder;

@end

NS_ASSUME_NONNULL_BEGIN

@interface SDBCoder : NSObject

@end

NS_ASSUME_NONNULL_END
