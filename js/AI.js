function AI(robot,view,delta) {
    if (view.length==0) {
        if (robot.t.xVisits==undefined) {
            robot.t.xVisits = Array(ARENA_SIZE).fill(0);
            robot.t.yVisits = Array(ARENA_SIZE).fill(0);
        }
        var cx=Math.floor(robot.x);
        var cy=Math.floor(robot.y);
        if (cx!=Math.floor(robot.t.px||0)||cy!=Math.floor(robot.t.py||0)) {
            robot.t.xVisits[cx]+=Math.random();
            robot.t.yVisits[cy]+=Math.random();
        }
        // find best candidates
        var bests={x:{"p":{"s":-1,"i":-1},"n":{"s":-1,"i":-1}},y:{"p":{"s":-1,"i":-1},"n":{"s":-1,"i":-1}}};
        var s=Math.sqrt(Math.pow(robot.s.sight,2)*2);
        for (var i=1; i<ARENA_SIZE; ++i) {
            var xpos=cx+i;
            var done=0;
            if (xpos<ARENA_SIZE - s) {
                var score = robot.t.xVisits[xpos]+i;
                if (bests.x.p.i==-1 || score<bests.x.p.s) {
                    bests.x.p.i=xpos;
                    bests.x.p.s=score;
                }
            } else ++done;
            var xneg=cx-i;
            if (xneg>=s) {
                var score = robot.t.xVisits[xneg]+i;
                if (bests.x.n.i==-1 || score<bests.x.n.s) {
                    bests.x.n.i=xneg;
                    bests.x.n.s=score;
                }
            } else ++done;
            var ypos=cy+i;
            if (ypos<ARENA_SIZE - s) {
                var score = robot.t.yVisits[ypos]+i;
                if (bests.y.p.i==-1 || score<bests.y.p.s) {
                    bests.y.p.i=ypos;
                    bests.y.p.s=score;
                }
            } else ++done;
            var yneg=cy-i;
            if (yneg>=s) {
                var score = robot.t.yVisits[yneg]+i;
                if (bests.y.n.i==-1 || score<bests.y.n.s) {
                    bests.y.n.i=yneg;
                    bests.y.n.s=score;
                }
            } else ++done;
            if (done==4) break;
        }
        if (G.debug) {
            G.debug=false;
            console.log(bests);
        }
        var xPos=bests.x.p.i;
        if (bests.x.p.i==-1 || (bests.x.n.s!=-1 && bests.x.n.s<bests.x.p.s)) xPos=bests.x.n.i;
        var yPos=bests.y.p.i;
        if (bests.y.p.i==-1 || (bests.y.n.s!=-1 && bests.y.n.s<bests.y.p.s)) yPos=bests.y.n.i;
        var nx=xPos-cx;
        var ny=yPos-cy;
        var m=magnitude(nx,ny)*20;
        robot.t.vx=(robot.t.vx||0)*0.95+nx/m;
        robot.t.vy=(robot.t.vy||0)*0.95+ny/m;
    } else {
        robot.t.vx = robot.t.vy = 0;
    }
    robot.t.px = robot.x;
    robot.t.py = robot.y;
}
