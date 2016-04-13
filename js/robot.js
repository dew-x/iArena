function Robot(name) {
    this.stats = {};
    this.points = 100;
    this.htmlID = null;
    this.name=name;
    for (var stat of ROBOT_STATS) {
        this.stats[stat]=1;
    }
    this.increaseStat = function (stat) {
        if (this.stats[stat]<MAXSTAT && this.points>=this.stats[stat]) {
            this.points-=this.stats[stat];
            ++this.stats[stat];
            this.doUI(this.htmlID);
        }
    }
    this.decreaseStat = function (stat) {
        if (this.stats[stat]>1) {
            --this.stats[stat];
            this.points+=this.stats[stat];
            this.doUI(this.htmlID);
        }
    }
    this.doUI = function (htmlID) {
        this.htmlID=htmlID;
        var parent=document.getElementById(htmlID);
        while (parent.firstChild) {
            parent.removeChild(parent.firstChild);
        }
        var elem=document.createElement("DIV");
        var name=document.createElement("H3");
        name.innerText=this.name;
        elem.appendChild(name);
        for (var statname in this.stats) {
            var stat=document.createElement("DIV");
            var plus=document.createElement("INPUT");
            plus.type="button";
            plus.value="+";
            plus.onclick=this.increaseStat.bind(this,statname);
            var rest=document.createElement("INPUT");
            rest.type="button";
            rest.value="-";
            rest.onclick=this.decreaseStat.bind(this,statname);
            var value=document.createElement("SPAN");
            value.innerText=statname+"["+this.stats[statname]+"]";
            stat.appendChild(rest);
            stat.appendChild(value);
            stat.appendChild(plus);
            elem.appendChild(stat);
        }
        var points=document.createElement("DIV");
        points.innerText="Points: "+this.points;
        elem.appendChild(points);
        parent.appendChild(elem);
    }
}
