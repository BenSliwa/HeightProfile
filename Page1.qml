import QtQuick 2.7

Page1Form {
    property variant m_heightProfile

    Component.onCompleted:
    {
        ElevationAPI.heightProfileReceived.connect(onHeightProfileReception);
    }

    function onHeightProfileReception(_profile)
    {
        console.log("onHeightProfileReception " + _profile.length)

        m_heightProfile = _profile;

        canvas.requestPaint();
    }

    function drawPath()
    {
        var context = canvas.getContext('2d');
        context.beginPath();
        for(var i=0; i<m_heightProfile.length; i++)
        {
            var entry = m_heightProfile[i];
            var latitude = entry["latitude"];
            var longitude = entry["longitude"];
            var elevation = entry["elevation"];

            var distance = 100;

            //console.log(latitude, longitude, elevation)

            var x = distance * i;
            var y = elevation ;

            console.log(x, y)

            if(i==0)
                context.moveTo(x, canvas.height-y);

            context.lineTo(x, canvas.height-y);
        }

        context.lineWidth = 3;
        context.strokeStyle = 'blue';
        context.stroke();
    }

    Canvas {
      id:canvas
      anchors.fill: parent
      height: 500

      onPaint:{
          drawPath();
      }
    }
}
