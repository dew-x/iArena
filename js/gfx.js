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
