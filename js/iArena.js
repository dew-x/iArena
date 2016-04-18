var G = {
    robotA: null,
    robotB: null,
    arena: null,
}

var ROBOT_STATS = [
    "lives",
    "range",
    "armor",
    "damage",
    "sight",
    "speed",
    "depth",
];

var MAXSTAT = 5;
var ARENA_SIZE = 25;
var ARENA_BORDER = 1;
var PLAYER_RADIUS = 1/ARENA_SIZE;

window.onload = function () {
    G.robotA = new Robot("A");
    G.robotB = new Robot("B");
    G.arena = new Arena();
    // render A
    G.robotA.doUI("robotA");
    // render B
    G.robotB.doUI("robotB");
    // prepare Arena
    G.arena.init("arena");
    G.arena.addRobot(G.robotA,0);
    G.arena.addRobot(G.robotB,1);
}

document.onkeypress=function(e){
    if (e.which==114) G.arena.reset();
};
