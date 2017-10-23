//
//  STTaterCommunicator.h
//  Sttarter
//
//  Created by Prajna Shetty on 25/01/17.
//  Copyright © 2017 Spurtree. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DownloadManager.h"
#import <JSONModel/JSONModel.h>
#import <MQTTClient/MQTTClient.h>
#import <MQTTClient/MQTTSessionManager.h>
#import "TopicsModel.h"
#import "GetMessagesModel.h"
#import "NSString+MD5.h"

#import "DatabaseHandler.h"
#import "Topics+CoreDataClass.h"
#import "GetRefCodeModel.h"
#import "MyTopicsModel.h"
#import "Topic_GroupMembers.h"


typedef void (^createGroupBlock)(BOOL isSuccess,NSString *groupTopic);
typedef void (^addAMemberToGroupBlock)(BOOL isSuccess,NSString *status);
typedef void (^addMembersToGroupBlock)(BOOL isSuccess,NSString *status);



@protocol STTCommunicatorDelegate <NSObject>
-(void)NotConnectedToInternet:(NSString*)userInfo;
@end


@interface STTaterCommunicator : NSObject<MQTTSessionDelegate,MQTTSessionManagerDelegate>
{
    MQTTCFSocketTransport *transport;
    MQTTSession *session;
    TopicsModel *_TopicsModel;
    BOOL isLoggedOut;
}
@property (nonatomic,strong) id <STTCommunicatorDelegate> delegate;

@property (nonatomic) UInt16 deliveredMessageMid;
@property (strong, nonatomic) NSMutableDictionary *dctMsgStatus;

@property (readonly, strong, nonatomic) NSManagedObjectContext *managedObjectContext;
@property (readonly, strong, nonatomic) NSManagedObjectModel *managedObjectModel;
@property (readonly, strong, nonatomic) NSPersistentStoreCoordinator *persistentStoreCoordinator;

+ (STTaterCommunicator*)sharedCommunicatorClass;

- (void)getUnreadMessageCountForTopic:(NSString*)strTopic;
- (void)updateMessageRead:(NSString*)strTopic;
- (void)addTopic:(NSString*)strUserName;
-(void)ReConnectCommunicator;
-(void)ConnectCommunicator;


- (void)subscribeInitialize;
- (void)getBuzzMessagesAppToken;
- (void)getmytopics;
- (void)saveContext;

- (NSURL *)applicationDocumentsDirectory;
- (NSMutableArray*)getAllMyTopics;
- (void)SttarterClassPublishTopic:(NSString*)strTopic messagehash:(NSString*)strHash strData:(NSDictionary*)dctMessage;//group

- (void)SendMessageToUserId:(NSString*)strUserId withMessage:(NSString*)strMessage;// single id
- (void)SendMessageToGroupWithTopic:(NSString*)strTopic withMessage:(NSString*)strMessage;// single id
-(void)getMessagesForTopic:(NSString*)strTopic;

- (void)logoutUser;
- (void)updateTopic;

- (int)getCountForTopic:(NSString*)strTopicId;
- (void)updateMessages:(NSString*)strTopic;

-(int)getCountAccrossAllTopics;
-(void)synchronizeAllMessages;
- (TopicMessageDetailEntity*)getLatestMessageObject:(NSString*)strTopicId;

///------
- (NSMutableArray*)getAllMessageForTopic:(NSString*)strTopicId;///***
/// Groups API
-(void)addAMemeberToGroupWithTopic:(NSString*)strTopic withMember:(NSString*)member completionBlock:(addAMemberToGroupBlock)completionBlock;

-(void)addMultipleMemebersToGroupWithTopic:(NSString*)strTopic withMember:(NSMutableArray*)arrMembers completionBlock:(addMembersToGroupBlock)completionBlock;  /// new !@#$ needs to be tested new API. API does not work.

//addMembersToGroupBlock

-(void)createNewGroup:(NSString*)strGroupName withMembers:(NSMutableArray*)membersArray Meta:(NSString*)strMeta completionBlock:(createGroupBlock)completionBlock;

-(NSString*)getUserMasterTopic:(NSString*)strTopic;



@end
