import QtQuick 2.7

Page1Form {
    button1.onClicked: {
        console.log("Button Pressed. Entered text: " + textField1.text);
    }


    Component.onCompleted:
    {
        ElevationAPI.elevationReplyReceived.connect(onElevationReplyReception);
    }

    function onElevationReplyReception(_positions)
    {
        console.log("onElevationReplyReception " + _positions.length)
    }

    Canvas {
      id:canvas
      anchors.fill: parent
      onPaint:{
         var context = canvas.getContext('2d');
          context.beginPath();
                context.moveTo(100, 20);

                // line 1
                context.lineTo(200, 160);

                // quadratic curve
                context.quadraticCurveTo(230, 200, 250, 120);

                // bezier curve
                context.bezierCurveTo(290, -40, 300, 200, 400, 150);

                // line 2
                context.lineTo(500, 90);

                context.lineWidth = 5;
                context.strokeStyle = 'blue';
                context.stroke();
      }
    }
}
