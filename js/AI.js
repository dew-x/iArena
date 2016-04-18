function AI(robot,view,delta) {
    if (view.length==0 || true) {
        if (robot.t.visited==undefined) {
            robot.t.visited = [];
        }
        if (robot.t.visited.length==0 || dist2(robot.x,robot.y,robot.t.visited[robot.t.visited.length-1].x,robot.t.visited[robot.t.visited.length-1].y)>1) robot.t.visited.push({x:robot.x,y:robot.y});
        if (robot.t.visited.length>100) robot.t.visited.shift();
        var x=Array(ARENA_SIZE).fill(0);
        var y=Array(ARENA_SIZE).fill(0);
        x[0]=100;
        y[0]=100;
        for (var i=0; i<robot.t.visited.length; ++i) {
            ++x[clamp(Math.round(robot.t.visited[i].x),0,ARENA_SIZE-1)];
            ++y[clamp(Math.round(robot.t.visited[i].y),0,ARENA_SIZE-1)];
        }
        var xPos=x.indexOf(x.min());
        var yPos=y.indexOf(y.min());
        console.log(xPos,yPos,x.min());
        robot.t.vx = xPos-robot.x;
        robot.t.vy = yPos-robot.y;
    } else {
        robot.t.vx = robot.t.vy = 0;
    }
}
