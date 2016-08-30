import QtQuick 2.7

Column
{
    Rectangle
    {
        height: 50
        width: parent.parent.width
        color: "red"
    }


    HeightProfile
    {
        width: parent.parent.width
        height: parent.parent.height-50
    }
}
