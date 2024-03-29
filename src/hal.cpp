#include "hal.h"

Hal::Hal(QObject *parent)
    : QObject{parent}
    , m_dpr(1)
    , m_physicalDotsPerInch(0)
    , m_devicePixelRatio(0)
    , m_debugMode(false)
    , m_externalStorageAccessGranted(false)
   // , permissions(nullptr)
{
#ifdef Q_OS_ANDROID
   //  permissions = new Permissions();
   //  qDebug() << "Before request permissions->getPermissionResult():" <<permissions->getPermissionResult();
  //   permissions->requestExternalStoragePermission();
   //  qDebug() << "After request permissions->getPermissionResult():" <<permissions->getPermissionResult();
#else
    m_externalStorageAccessGranted = true;
#endif
}


void Hal::updateInfo(){

}

double Hal::getDevicePixelRatio() const{
    int density = 0;
#ifdef Q_OS_ANDROID
    QAndroidJniEnvironment env;

    //  BUG with dpi on some androids: https://bugreports.qt-project.org/browse/QTBUG-35701
    QAndroidJniObject qtActivity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return EXIT_FAILURE;
    }

    QAndroidJniObject resources = qtActivity.callObjectMethod("getResources", "()Landroid/content/res/Resources;");
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return EXIT_FAILURE;
    }

    QAndroidJniObject displayMetrics = resources.callObjectMethod("getDisplayMetrics", "()Landroid/util/DisplayMetrics;");
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return EXIT_FAILURE;
    }

    density = displayMetrics.getField<int>("densityDpi");
#else
    density = m_physicalDotsPerInch * m_devicePixelRatio;
#endif

#ifdef QT_DEBUG
    density = 320;
#endif
    return   density >= 480 ? 3 :
                              density >= 320 ? 2 :
                                               density >= 240 ? 1.5 : 1;
}

bool Hal::getDebugMode() const
{
    return m_debugMode;
}

bool Hal::externalStorageAccessGranted() const
{
    return m_externalStorageAccessGranted;
}

void Hal::setDebugMode(bool newDebugmode){
    if (m_debugMode == newDebugmode){
        return;
    }
    m_debugMode = newDebugmode;
}

void Hal::setDotsPerInch(qreal m_dpi)
{
    if (m_physicalDotsPerInch == m_dpi){
        return;
    }
    m_physicalDotsPerInch = m_dpi;
}

void Hal::setDevicePixelRatio(qreal m_dpr)
{
    if (m_devicePixelRatio == m_dpr){
        return;
    }
     m_devicePixelRatio = m_dpr;
}

/*!
 * \brief Make docs encourage readers to query locale right
 * \sa https://codereview.qt-project.org/c/qt/qtdoc/+/297560
 */
void Hal::createAppFolder(){
    ///TODO check permissions
    QDir dirAppConfig( QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) );
    if (dirAppConfig.exists() == false) {
        dirAppConfig.mkpath(dirAppConfig.path());
    }
    QDir dirAppData( QStandardPaths::writableLocation(QStandardPaths::AppDataLocation ) );
    if (dirAppData.exists() == false) {
        dirAppData.mkpath(dirAppData.path());
    }
}
