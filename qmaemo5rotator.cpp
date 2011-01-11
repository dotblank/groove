
#include "qmaemo5rotator.h"
#if defined(Q_WS_MAEMO_5) || defined(Q_WS_HILDON)
#include <mce/dbus-names.h>
#include <mce/mode-names.h>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusMessage>


QMaemo5Rotator::QMaemo5Rotator(RotationBehavior behavior, QWidget *parent)
    : QObject(parent),
    isSetUp(false)
{
    setCurrentBehavior(behavior);
}

QMaemo5Rotator::~QMaemo5Rotator()
{
    QDBusConnection::systemBus().call(QDBusMessage::createMethodCall(MCE_SERVICE, MCE_REQUEST_PATH, MCE_REQUEST_IF, MCE_ACCELEROMETER_DISABLE_REQ));
}

const QMaemo5Rotator::RotationBehavior QMaemo5Rotator::currentBehavior()
{
    return _currentBehavior;
}

const QMaemo5Rotator::Orientation QMaemo5Rotator::currentOrientation()
{
    return _currentOrientation;
}

void QMaemo5Rotator::setCurrentBehavior(QMaemo5Rotator::RotationBehavior value)
{
    if (value == _currentBehavior && isSetUp)
        return;

    isSetUp = true;
    _currentBehavior = value;

    if (value == QMaemo5Rotator::AutomaticBehavior)
    {
        QDBusConnection::systemBus().call(QDBusMessage::createMethodCall(MCE_SERVICE, MCE_REQUEST_PATH, MCE_REQUEST_IF, MCE_ACCELEROMETER_ENABLE_REQ));
        QDBusConnection::systemBus().connect(QString(), MCE_SIGNAL_PATH, MCE_SIGNAL_IF, MCE_DEVICE_ORIENTATION_SIG, this, SLOT(on_orientation_changed(QString)));
    }
    else
    {
        QDBusConnection::systemBus().call(QDBusMessage::createMethodCall(MCE_SERVICE, MCE_REQUEST_PATH, MCE_REQUEST_IF, MCE_ACCELEROMETER_DISABLE_REQ));

        if (value == QMaemo5Rotator::PortraitBehavior)
        {
            setCurrentOrientation(QMaemo5Rotator::PortraitOrientation);
        }
        else
        {
            setCurrentOrientation(QMaemo5Rotator::LandscapeOrientation);
        }
    }
}
void QMaemo5Rotator::test()
{
    QMaemo5Rotator::setRotation(up);
}

void QMaemo5Rotator::setCurrentOrientation(QMaemo5Rotator::Orientation value)
{
    _currentOrientation = value;
    QWidget *par = (QWidget*)parent();

    switch (value)
    {
    case QMaemo5Rotator::PortraitOrientation:
        if (par != NULL)
        {
            par->setAttribute(Qt::WA_Maemo5LandscapeOrientation, false);
            par->setAttribute(Qt::WA_Maemo5PortraitOrientation, true);
        }
        orientationChanged(QMaemo5Rotator::PortraitOrientation);
        break;
    case QMaemo5Rotator::LandscapeOrientation:
        if (par != NULL)
        {
            par->setAttribute(Qt::WA_Maemo5PortraitOrientation, false);
            par->setAttribute(Qt::WA_Maemo5LandscapeOrientation, true);
        }
        orientationChanged(QMaemo5Rotator::LandscapeOrientation);

        break;
    }
}

void QMaemo5Rotator::on_orientation_changed(const QString& newOrientation)
{
    if (newOrientation == QLatin1String(MCE_ORIENTATION_PORTRAIT) || newOrientation == QLatin1String(MCE_ORIENTATION_PORTRAIT_INVERTED))
    {
        setCurrentOrientation(QMaemo5Rotator::PortraitOrientation);
    }
    else
    {
        setCurrentOrientation(QMaemo5Rotator::LandscapeOrientation);
    }
    QApplication::desktop()->updateGeometry();
}







static bool QMaemo5Rotator::setRotation(direction dir)
{
    Rotation rotation = dir;
    int reflection = 0;
    Display * dpy = XOpenDisplay(NULL);
    if ( dpy == NULL )
    {
        printf ( "Cannot open display %s\n", displayname ) ;
        return false ;
    }
    int screen = DefaultScreen ( dpy ) ;
    Window root = RootWindow ( dpy, screen ) ;

    XSelectInput (dpy, root, StructureNotifyMask);
    XRRSelectInput (dpy, root, RRScreenChangeNotifyMask);
    int eventbase ;
    int errorbase ;
    XRRQueryExtension ( dpy, &eventbase, &errorbase ) ;

    XRRScreenConfiguration * sc = XRRGetScreenInfo (dpy, root);
    if ( sc == NULL )
    {
        printf ( "Cannot get screen info\n" ) ;
        return false ;
    }
    int nsize ;
    XRRScreenSize * sizes = XRRConfigSizes(sc, &nsize);
    int sizeindex = 0 ;
    if ( nsize = 0 )
    {
        printf ( "XRandr not available\n") ;
        return false ;
    }
    Status status = XRRSetScreenConfig ( dpy, sc, DefaultRootWindow (dpy), (SizeID) sizeindex, (Rotation) (rotation | reflection), CurrentTime);
    XEvent event;
    bool rcvdrrnotify = false ;
    bool rcvdconfignotify = false ;
    if ( status == RRSetConfigSuccess)
    {
        printf("Screen rotation changed");
    }
    XCloseDisplay(dpy);
    return true ;
}
#endif
