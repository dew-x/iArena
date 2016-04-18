function Arena() {
    this.robots=[];
    this.teams={};
    this.ctx=null;
    this.players=[];
    this.init = function (htmlID) {
        var parent=document.getElementById(htmlID);
        while (parent.firstChild) {
            parent.removeChild(parent.firstChild);
        }
        var rect=parent.getBoundingClientRect();
        var canvas=document.createElement("CANVAS");
        this.width=canvas.width=rect.width;
        this.height=canvas.height=rect.height;
        this.size=Math.min(this.width,this.height);
        this.x0=(this.width-this.size)/2;
        this.y0=(this.height-this.size)/2
        parent.appendChild(canvas);
        this.ctx=canvas.getContext("2d");
        this.step();
    }
    this.addRobot = function (robot, teamID) {
        this.robots.push(robot);
        this.teams[teamID]=this.teams[teamID]||[];
        this.teams[teamID].push(robot);
        this.reset();
    }
    this.reset = function () {
        this.players=[];
        for (var i=0; i<this.robots.length; ++i) {
            this.players.push({
                x:ARENA_SIZE*(PLAYER_RADIUS+Math.random()*(1-PLAYER_RADIUS*2)),
                y:ARENA_SIZE*(PLAYER_RADIUS+Math.random()*(1-PLAYER_RADIUS*2)),
                s:this.robots[i].getStats(),
                t:{},
            });
        }
    }
    this.update = function (delta) {
        for (var i=0; i<this.players.length; ++i) {
            AI(this.players[i],this.makeView(i),delta);
        }
        for (var i=0; i<this.players.length; ++i) {
            var m=magnitude(this.players[i].t.vx,this.players[i].t.vy);
            if (m>1) {
                this.players[i].t.vx/=m;
                this.players[i].t.vy/=m;
            }
            this.players[i].x += this.players[i].t.vx*delta/1000*this.players[i].s.speed;
            this.players[i].y += this.players[i].t.vy*delta/1000*this.players[i].s.speed;
            this.players[i].x = clamp(this.players[i].x,ARENA_BORDER,ARENA_SIZE-ARENA_BORDER);
            this.players[i].y = clamp(this.players[i].y,ARENA_BORDER,ARENA_SIZE-ARENA_BORDER);
        }
    }
    this.makeView = function (pID) {
        var ret=[];
        for (var i=0; i<this.players.length; ++i) {
            if (i!=pID) {
                if (dist2(this.players[pID].x,this.players[pID].y,this.players[i].x,this.players[i].y)<=this.players[pID].s.sight*2+1) {
                    ret.push({
                        id:i,
                        team:i,
                        x:this.players[i].x-this.players[pID].x,
                        y:this.players[i].y-this.players[pID].y
                    });
                }
            }
        }
        return ret;
    }
    this.toScreen = function (v) {
        return v/ARENA_SIZE*this.size;
    }
    this.drawPlayer = function (s) {
        // sight
        drawCircle(this.ctx,0,0,(s.sight*2+1)/ARENA_SIZE*this.size,"rgba(100,100,255,0.1)");
        // range
        drawCircle(this.ctx,0,0,(s.range*2)/ARENA_SIZE*this.size,"rgba(255,100,100,0.2)");
        // player
        drawCircle(this.ctx,0,0,PLAYER_RADIUS*this.size,"orange",null);
        // defenses
        for (var i=0; i<s.armor; ++i) {
            drawCircle(this.ctx,0,0,PLAYER_RADIUS*this.size+2*(i+1),null,"gray",3,[5]);
        }

    }
    this.draw = function () {
        this.ctx.clearRect(0,0,this.width,this.height);
        this.ctx.save();
        this.ctx.translate(this.x0,this.y0);
        this.ctx.fillStyle="silver";
        this.ctx.fillRect(0,0,this.size,this.size);
        for (var i=0; i<this.players.length; ++i) {
            this.ctx.fillStyle="orange";
            this.ctx.save();
            this.ctx.translate(this.toScreen(this.players[i].x),this.toScreen(this.players[i].y));
            this.drawPlayer(this.players[i].s);
            this.ctx.restore();
        }
        this.ctx.restore();
    }
    this.step = function () {
        var delta=16;
        this.update(delta);
        this.draw();
        window.requestAnimationFrame(this.step.bind(this));
    }
}
