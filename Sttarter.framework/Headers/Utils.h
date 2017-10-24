//
//  Utils.h
//  Sttarter
//
//  Created by Prajna Shetty on 27/02/17.
//  Copyright © 2017 Spurtree. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Reachability/Reachability.h>

@interface Utils : NSObject

+(Utils*)shared;

- (NSString*)GetCurrentEpochTime;
- (NSString*)getClientId;
- (BOOL)checkIfInternetConnectionExists;
- (void)reachabilityDidChange:(NSNotification *)notification;

@end
