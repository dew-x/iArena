function dist2(x0,y0,x1,y1) {
    return Math.sqrt(Math.pow(x1-x0,2)+Math.pow(y1-y0,2));
}
function magnitude(x,y) {
    return Math.sqrt(Math.pow(x,2)+Math.pow(y,2));
}
function clamp(v,min,max) {
    return Math.max(Math.min(v,max),min);
}

Array.prototype.max = function() {
  return Math.max.apply(null, this);
};

Array.prototype.min = function() {
  return Math.min.apply(null, this);
};
