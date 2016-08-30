.pragma library



function drawPath(_canvas, _data, _lineWidth, _color, _type)
{
    var context = _canvas.getContext('2d');
    context.beginPath();
    for(var i=0; i<_data.length; i++)
    {
        var coord = _data[i];
        var x = coord[0];
        var y = coord[1];

        if(i==0)
            context.moveTo(x, _canvas.height-y);

        context.lineTo(x, _canvas.height-y);
    }

    context.lineWidth = _lineWidth;

    if(_type=="fill")
    {
        context.fillStyle = _color;
        context.fill();
    }
    else if(_type=="stroke")
    {
        context.strokeStyle = _color;
        context.stroke();
    }
}

function writeText(_canvas, _text, _x, _y, _fontSize, _color, _font, _align)
{
    var context = _canvas.getContext('2d');
    var font = String(_fontSize) + "px " + _font;
    context.font = font;
    context.fillStyle = _color;
    context.textAlign = _align;
    context.fillText(_text, _x, _canvas.height-_y);
}

function writeTextVertival(_canvas, _text, _x, _y, _fontSize, _color, _font, _align)
{
    var context = _canvas.getContext('2d');
    context.save();
    context.translate( _x, _canvas.height-_y);
    context.rotate(-Math.PI/2);
    context.textAlign = "center";

    var font = String(_fontSize) + "px " + _font;
    context.font = font;
    context.fillStyle = _color;
    context.textAlign = _align;
    context.fillText(_text, 0, 0);

    context.restore();



}

