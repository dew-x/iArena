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
            });
        }
    }
    this.update = function (delta) {

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
