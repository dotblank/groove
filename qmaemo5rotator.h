#ifndef QMAEMO5ROTATOR_H
#define QMAEMO5ROTATOR_H
//----------
// Provides a means of WORKING automatic rotation for Maemo 5 apps. (The default Qt solution is buggy.)
//----------

#include <Qt>
#include <QtGui>
#include <QtCore>
#include <X11/extensions/Xrandr.h>
#include <X11/Xlib.h>

class QMaemo5Rotator : private QObject
{

    Q_OBJECT

public:

    enum RotationBehavior
    {
        AutomaticBehavior = 0,
        LandscapeBehavior = 1,
        PortraitBehavior = 2
    };
    enum direction
    {
        up = RR_Rotate_180,
        down = RR_Rotate_0,
        right = RR_Rotate_90,
        left = RR_Rotate_270
    };

    enum Orientation
    {
        LandscapeOrientation = 0,
        PortraitOrientation = 1
    };

private:

    bool isSetUp;
    RotationBehavior _currentBehavior;
    Orientation _currentOrientation;
    //bool setRotation(direction);

public:

    explicit QMaemo5Rotator(RotationBehavior behavior = LandscapeBehavior, QWidget *parent = NULL);
    ~QMaemo5Rotator();

    const RotationBehavior currentBehavior();
    const Orientation currentOrientation();
    void setCurrentBehavior(RotationBehavior value);
    void setCurrentOrientation(Orientation value);
    //void test();

private slots:

    void on_orientation_changed(const QString& newOrienation);

signals:

    void orientationChanged(Orientation orientation);

};
#endif // QMAEMO5ROTATOR_H
