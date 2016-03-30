#include "AppDelegate.h"
#include "GameMenuScene.h"
#include "GameMainScene.h"
#include "UIManager.h"
#include "MusicManager.h"
#if defined( PAY_WITH_UMENG )
#include "MobClickCpp.h"
#endif

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	pEGLView->setDesignResolutionSize( 480, 854, kResolutionShowAll );

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene =  GameMenuScene::scene();// HelloWorld::scene();
	//CCScene *pScene =  GameMainScene::scene();
    // run
    pDirector->runWithScene(pScene);

	CCDictionary* dic = CCDictionary::createWithContentsOfFile( "cn.xml" );
	CCString* strChannel = (CCString*)dic->objectForKey("channelId");
#if defined( PAY_WITH_UMENG )
	MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("5513cc34fd98c5ce0800048f", strChannel->getCString());
#endif
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

	if (MusicManager::GetInstance() != NULL)
	{
		MusicManager::GetInstance()->Stop();
	}
#if defined( PAY_WITH_UMENG )
	umeng::MobClickCpp::applicationDidEnterBackground();
#endif
    // if you use SimpleAudioEngine, it must be pause
    
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
	bool musicStoped = CCUserDefault::sharedUserDefault()->getBoolForKey("musicStop");
	if (MusicManager::GetInstance() != NULL && !musicStoped)
	{
		MusicManager::GetInstance()->Open();
	}

	if(UIManager::GetInstance()->getStopMenuUI()!=NULL)
	{
		UIManager::GetInstance()->getStopMenuUI()->activate();
	}
#if defined( PAY_WITH_UMENG )
	umeng::MobClickCpp::applicationWillEnterForeground();
#endif
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
