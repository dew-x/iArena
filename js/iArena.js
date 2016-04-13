var G = {
    robotA: null,
    robotB: null,
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

window.onload = function () {
    G.robotA = new Robot();
    G.robotB = new Robot();
    // render A
    G.robotA.doUI("robotA");
    // render B
    G.robotB.doUI("robotB");
    // prepare Arena
}
