function drawCircle(ctx,x,y,r,fillColor,strokeColor,strokeWidth,lineDash) {
    ctx.beginPath();
    ctx.arc(x,y,r,0,2*Math.PI);
    ctx.closePath();
    if (fillColor) {
        ctx.fillStyle=fillColor;
        ctx.fill();
    }
    if (strokeColor) {
        ctx.strokeStyle=fillColor;
        if (strokeWidth) ctx.strokeWidth = strokeWidth;
        if (lineDash) {
            if (typeof lineDash==="object") ctx.setLineDash(lineDash);
            else ctx.setLineDash([lineDash]);
        }
        ctx.stroke();
    }
}

function drawLine(ctx,x0,y0,x1,y1,color,width) {
    ctx.beginPath();
    ctx.moveTo(x0,y0);
    ctx.lineTo(x1,y1);
    ctx.closePath();
    if (color) {
        if (width) {
            ctx.strokeWidth = width;
        }
        ctx.strokeStyle=color;
        ctx.stroke();
    }
}
