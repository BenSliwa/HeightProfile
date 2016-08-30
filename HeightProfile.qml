import QtQuick 2.7
import "Canvas.js" as CanvasLib
import "UiSettings.js" as Ui

Rectangle {
    anchors.fill: parent
    color: Ui.CANVAS_COLOR;

    property variant m_data

    property double m_minElevation
    property double m_maxElevation
    property double m_minDistance: 0
    property double m_maxDistance

    property variant m_measurementHeight: 20;
    property variant m_baseStationHeight: 20;


    Component.onCompleted:
    {
        ElevationAPI.heightProfileReceived.connect(onHeightProfileReception);
    }

    function onHeightProfileReception(_data, _minElevation, _maxElevation, _maxDistance)
    {
        console.log("onHeightProfileReception", _data.length, _minElevation, _maxElevation)

        m_data = _data;
        m_minElevation = _minElevation.toFixed(2);
        m_maxElevation = _maxElevation.toFixed(2);
        m_maxDistance = _maxDistance;

        canvas.requestPaint();
    }

    function drawPath()
    {
        m_minDistance = 0;
        var data = [];
        for(var i=0; i<m_data.length; i++)
        {
            var entry = m_data[i];
            var latitude = entry["latitude"];
            var longitude = entry["longitude"];
            var elevation = entry["elevation"];
            var distance = (canvas.width-Ui.PROFILE_LEFT_PADDING-Ui.PROFILE_RIGHT_PADDING)/m_data.length;

            var x = distance * i + Ui.PROFILE_LEFT_PADDING;
            var y = scaleElevation(elevation);

            if(i==0)
                data.push([x, Ui.PROFILE_BOTTOM_PADDING]);


            data.push([x, y]);

            if(i==m_data.length-1)
                data.push([x, Ui.PROFILE_BOTTOM_PADDING]);
       }

        CanvasLib.drawPath(canvas, data, Ui.PROFILE_WIDTH, Ui.PROFILE_FILL_COLOR, "fill");
        drawGrid();
        CanvasLib.drawPath(canvas, data, Ui.PROFILE_WIDTH, Ui.PROFILE_STROKE_COLOR, "stroke");

     //   drawLOS();

        canvas.save(UiManager.getFileName());
    }

    function scaleElevation(_elevation)
    {
        return Ui.PROFILE_BOTTOM_PADDING + _elevation / m_maxElevation * (canvas.height-Ui.PROFILE_BOTTOM_PADDING-Ui.PROFILE_TOP_PADDING);
    }

    function drawLOS()
    {
        if(m_data.length>2)
        {
            var data = [];
            var l = 3;

            var baseStationPoint = m_data[0];
            var baseStationElevation = baseStationPoint["elevation"];
            data.push([Ui.PROFILE_LEFT_PADDING, scaleElevation(baseStationElevation)]);
            data.push([Ui.PROFILE_LEFT_PADDING, scaleElevation(baseStationElevation + m_baseStationHeight)]);

            var measurementPoint = m_data[m_data.length-1];
            var measurementElevation = measurementPoint["elevation"];
            data.push([canvas.width-Ui.PROFILE_RIGHT_PADDING, scaleElevation(measurementElevation + m_measurementHeight)]);
            data.push([canvas.width-Ui.PROFILE_RIGHT_PADDING, scaleElevation(measurementElevation)]);

            CanvasLib.drawPath(canvas, data, l, "green", "stroke");
        }

    }

    function scalePoint(_point)
    {
        var point = _point;
        point[0] += Ui.PROFILE_LEFT_PADDING;
        point[1] += Ui.PROFILE_BOTTOM_PADDING;

        return point;
    }

    function drawGrid()
    {
        var data = [];
        var l = 1;


        CanvasLib.drawPath(canvas, data, l, Ui.GRID_COLOR, "stroke");

        for(var i=0; i<Ui.PROFILE_HEIGHT_STEPS; i++)
        {
            data = [];
            var y = Ui.PROFILE_BOTTOM_PADDING + i * (canvas.height-Ui.PROFILE_BOTTOM_PADDING-Ui.PROFILE_TOP_PADDING)/(Ui.PROFILE_HEIGHT_STEPS-1);
            var xMin = Ui.PROFILE_LEFT_PADDING-l;
            var xMax = canvas.width-Ui.PROFILE_RIGHT_PADDING-l;
            data.push([xMin, y+l]);
            data.push([xMax, y+l]);
            CanvasLib.drawPath(canvas, data, l, Ui.GRID_COLOR, "stroke");
        }

        for(var i=0; i<Ui.PROFILE_DISTANCE_STEPS; i++)
        {
            data = [];
            var x = Ui.PROFILE_LEFT_PADDING + i * (canvas.width-Ui.PROFILE_LEFT_PADDING-Ui.PROFILE_RIGHT_PADDING)/(Ui.PROFILE_DISTANCE_STEPS-1);
            var yMin = Ui.PROFILE_BOTTOM_PADDING;
            var yMax = canvas.height-Ui.PROFILE_TOP_PADDING;
            data.push([x-l, yMin]);
            data.push([x-l, yMax]);
            CanvasLib.drawPath(canvas, data, l, Ui.GRID_COLOR, "stroke");

            var s = 14;
            var distance = (m_maxDistance-m_minDistance)/ 1000 * i/(Ui.PROFILE_DISTANCE_STEPS-1);
            CanvasLib.writeText(canvas, String(distance), x-l, Ui.PROFILE_BOTTOM_PADDING-s, s, Ui.PROFILE_TEXT_COLOR, "Arial", "center");
        }



        CanvasLib.writeTextVertival(canvas, "Elevation [m] ", 70, canvas.height/2, s, Ui.PROFILE_TEXT_COLOR, "Arial", "center");


        CanvasLib.writeText(canvas, "Angle: " + String(UiManager.getAngle()) + "°", canvas.width/2, canvas.height-Ui.PROFILE_TOP_PADDING+10, s, Ui.PROFILE_TEXT_COLOR, "Arial", "center");

        var s = 14;
        CanvasLib.writeText(canvas, String(m_minElevation), 50, Ui.PROFILE_BOTTOM_PADDING, s, Ui.PROFILE_TEXT_COLOR, "Arial", "start");
        CanvasLib.writeText(canvas, String(m_maxElevation), 50, canvas.height-Ui.PROFILE_TOP_PADDING, s, Ui.PROFILE_TEXT_COLOR, "Arial", "start");


       // CanvasLib.writeText(canvas, String(m_minDistance/1000), Ui.PROFILE_LEFT_PADDING, Ui.PROFILE_BOTTOM_PADDING-s, s, Ui.PROFILE_TEXT_COLOR, "Arial", "center");
       // CanvasLib.writeText(canvas, String(m_maxDistance/1000), canvas.width-Ui.PROFILE_RIGHT_PADDING, Ui.PROFILE_BOTTOM_PADDING-s, s, Ui.PROFILE_TEXT_COLOR, "Arial", "center");
        CanvasLib.writeText(canvas, "Distance [km]", canvas.width/2, 10, s, Ui.PROFILE_TEXT_COLOR, "Arial", "center");


    }

    Canvas {
      id:canvas
      anchors.fill: parent

      onPaint:{
          drawPath();
      }
    }
}
