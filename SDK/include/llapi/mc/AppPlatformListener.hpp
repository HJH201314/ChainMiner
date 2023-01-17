/**
 * @file  AppPlatformListener.hpp
 * @note  This Header is auto generated by LiteLoaderBDS Toolchain.
 *
 */
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

/**
 * @brief MC class AppPlatformListener.
 *
 */
class AppPlatformListener {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
#ifndef DISABLE_CONSTRUCTOR_PREVENTION_APPPLATFORMLISTENER
public:
    class AppPlatformListener& operator=(class AppPlatformListener const &) = delete;
    AppPlatformListener(class AppPlatformListener const &) = delete;
#endif

public:
#ifdef ENABLE_VIRTUAL_FAKESYMBOL_APPPLATFORMLISTENER
    /**
     * @symbol ?onAppFocusGained@AppPlatformListener@@UEAAXXZ
     * @hash   -1171057293
     */
    MCVAPI void onAppFocusGained();
    /**
     * @symbol ?onAppFocusLost@AppPlatformListener@@UEAAXXZ
     * @hash   1370393081
     */
    MCVAPI void onAppFocusLost();
    /**
     * @symbol ?onAppPaused@AppPlatformListener@@UEAAXXZ
     * @hash   486028559
     */
    MCVAPI void onAppPaused();
    /**
     * @symbol ?onAppPreSuspended@AppPlatformListener@@UEAAXXZ
     * @hash   -47759719
     */
    MCVAPI void onAppPreSuspended();
    /**
     * @symbol ?onAppResumed@AppPlatformListener@@UEAAXXZ
     * @hash   393112148
     */
    MCVAPI void onAppResumed();
    /**
     * @symbol ?onAppSuspended@AppPlatformListener@@UEAAXXZ
     * @hash   1009520728
     */
    MCVAPI void onAppSuspended();
    /**
     * @symbol ?onAppTerminated@AppPlatformListener@@UEAAXXZ
     * @hash   -1520157724
     */
    MCVAPI void onAppTerminated();
    /**
     * @symbol ?onAppUnpaused@AppPlatformListener@@UEAAXXZ
     * @hash   1040955592
     */
    MCVAPI void onAppUnpaused();
    /**
     * @symbol ?onClipboardCopy@AppPlatformListener@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
     * @hash   -299615
     */
    MCVAPI void onClipboardCopy(std::string const &);
    /**
     * @symbol ?onClipboardPaste@AppPlatformListener@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
     * @hash   -1923061359
     */
    MCVAPI void onClipboardPaste(std::string const &);
    /**
     * @symbol ?onDeviceLost@AppPlatformListener@@UEAAXXZ
     * @hash   -955376136
     */
    MCVAPI void onDeviceLost();
    /**
     * @symbol ?onLowMemory@AppPlatformListener@@UEAAXXZ
     * @hash   -1035527147
     */
    MCVAPI void onLowMemory();
    /**
     * @symbol ?onOperationModeChanged@AppPlatformListener@@UEAAXW4OperationMode@@@Z
     * @hash   714024280
     */
    MCVAPI void onOperationModeChanged(enum class OperationMode);
    /**
     * @symbol ?onPerformanceModeChanged@AppPlatformListener@@UEAAX_N@Z
     * @hash   -931814835
     */
    MCVAPI void onPerformanceModeChanged(bool);
    /**
     * @symbol ?onPushNotificationReceived@AppPlatformListener@@UEAAXAEBVPushNotificationMessage@@@Z
     * @hash   -20354493
     */
    MCVAPI void onPushNotificationReceived(class PushNotificationMessage const &);
    /**
     * @symbol ?onResizeBegin@AppPlatformListener@@UEAAXXZ
     * @hash   1262029493
     */
    MCVAPI void onResizeBegin();
    /**
     * @symbol ?onResizeEnd@AppPlatformListener@@UEAAXXZ
     * @hash   1301410535
     */
    MCVAPI void onResizeEnd();
#endif
    /**
     * @symbol ??0AppPlatformListener@@QEAA@XZ
     * @hash   -1710345436
     */
    MCAPI AppPlatformListener();
    /**
     * @symbol ?terminate@AppPlatformListener@@QEAAXXZ
     * @hash   -1036979865
     */
    MCAPI void terminate();

};