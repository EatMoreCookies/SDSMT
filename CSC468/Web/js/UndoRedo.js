// JavaScript Document//helper class to handle the current location in the undo/redo list
var images = [
    "images/stickman-head_Default.png",
    "images/stickman-head_Pirate-hat.png",
    "images/stickman-head_Leprechaun-beard.png",
    "images/stickman-lArm_Default.png",
    "images/stickman-lArm_Pirate-hook.png",
    "images/stickman-lArm_Leprechaun-gold.png",
    "images/stickman-body_Default.png",
    "images/stickman-body_Pirate-belt.png",
    "images/stickman-body_Leprechaun-greenShirt.png",
    "images/stickman-rArm_Default.png",
    "images/stickman-rArm_Pirate-sword.png",
    "images/stickman-rArm_Leprechaun-shamrock.png",
    "images/stickman-legs_Default.png",
    "images/stickman-legs_Pirate-boots.png",
    "images/stickman-legs_Leprechaun-shoe.png" ]

var cookiesVars = [
    "head",
    "larm",
    "body",
    "rarm",
    "legs"]

var displayLocs = [
    "displayHead",
    "displayLArm",
    "displayBody",
    "displayRArm",
    "displayLegs" ]


function getLocation(name){
    if( name === "head")
        return "displayHead";

    else if( name === "larm")
        return "displayLArm";

    else if( name === "body")
        return "displayBody";

    else if( name === "rarm")
        return "displayRArm";

    else if( name === "legs")
        return "displayLegs";
}

function readCookies(cookies){
    let list = [];
    let index = -1;

    for( let i = 0; i < 5; ++i){
        index = cookies.search(cookiesVars[i])
        if(  index !== -1)
            list.push( cookies[index+5])
        else
            list.push(0);
    }
    return list;
}

// GRADING: MANAGE
class History {
    constructor(){
        this.UndoRedos =[];
        this.index = 0;
    }


    //new UndoRedo, remove everything after the current UndoRedo index
    //and append the new function
    executeAction(cmd){
        this.UndoRedos.length = this.index; //trims length from 0 to index
        this.UndoRedos.push(cmd);
        this.index = this.UndoRedos.length

        //run the UndoRedo and update
        cmd.exec();
        updateUI();
    }


    //undo called. Call the undo function on the current UndoRedo and move back one
    undoCmd(){
        if(this.index > 0)
        {
            let cmd = this.UndoRedos[this.index-1];
            cmd.undo();
            this.index= this.index - 1;

            updateUI();
        }
    }

    //redo called. Call the execution function on the current UndoRedo and move forward one
    redoCmd(){
        if(this.index < this.UndoRedos.length)
        {
            var cmd = this.UndoRedos[this.index];
            cmd.exec();
            this.index = this.index + 1;
            updateUI();
        }
    }

    //is undo available
    canUndo(){
        return this.index != 0;
    }

    //is redo available
    canRedo(){
        return this.index < this.UndoRedos.length;
    }
}


// GRADING: ACTION
class UndoRedo {
    constructor(image, name, value) {
        this.image = image;
        this.name = name;
        this.value = value;
        this.prevState = document.cookie;
    }

    exec() {
        if (this.image !== "all") {
            document.cookie = this.name + "=" + this.value;
            document.getElementById(getLocation(this.name)).src = this.image;
        } else {
            this.doAll();
        }

    }

    undo() {
        let list = readCookies(this.prevState);

        let index = 0;

        for( let i = 0; i < 5; ++i ){
            document.cookie = cookiesVars[i] + "=" + list[i];
            document.getElementById(displayLocs[i]).src = images[parseInt(list[i]) + index];
            index += 3;
        }
    }

    doAll() {
        let index = 0;

        for( let i = 0; i < 5; ++i ){
            document.cookie = cookiesVars[i] + "=" + this.value;
            document.getElementById(displayLocs[i]).src = images[this.value + index];
            index += 3;
        }
    }
}


// GRADING: COMMAND
function BodyEvent(event) {

    // Head
    if( event.target.id === "DefaultHead" )
        hist.executeAction(new UndoRedo(images[0], "head", 0));
    else if( event.target.id === "PirateHead" )
        hist.executeAction(new UndoRedo(images[1], "head", 1));
    else if( event.target.id === "LepHead" )
        hist.executeAction(new UndoRedo(images[2], "head", 2));

    // Left Arm
    else if( event.target.id === "DefaultLArm" )
        hist.executeAction(new UndoRedo(images[3], "larm", 0));
    else if( event.target.id === "PirateLArm" )
        hist.executeAction(new UndoRedo(images[4], "larm", 1));
    else if( event.target.id === "LepLArm" )
        hist.executeAction(new UndoRedo(images[5], "larm", 2));

    // Body
    else if( event.target.id === "DefaultBody" )
        hist.executeAction(new UndoRedo(images[6], "body", 0));
    else if( event.target.id === "PirateBody" )
        hist.executeAction(new UndoRedo(images[7], "body", 1));
    else if( event.target.id === "LepBody" )
        hist.executeAction(new UndoRedo(images[8], "body", 2));

    // Right Arm
    else if( event.target.id === "DefaultRArm" )
        hist.executeAction(new UndoRedo(images[9], "rarm", 0));
    else if( event.target.id === "PirateRArm" )
        hist.executeAction(new UndoRedo(images[10], "rarm", 1));
    else if( event.target.id === "LepRArm" )
        hist.executeAction(new UndoRedo(images[11], "rarm", 2));

    // Legs
    else if( event.target.id === "DefaultLegs" )
        hist.executeAction(new UndoRedo(images[12],  "legs", 0));
    else if( event.target.id === "PirateLegs" )
        hist.executeAction(new UndoRedo(images[13],  "legs", 1));
    else if( event.target.id === "LepLegs" )
        hist.executeAction(new UndoRedo(images[14],  "legs", 2));

    else if( event.target.id === "Default" )
        hist.executeAction(new UndoRedo("all", null, 0));
    else if( event.target.id === "Pirate" )
        hist.executeAction(new UndoRedo("all", null, 1));
    else if( event.target.id === "Leprechaun" )
        hist.executeAction(new UndoRedo("all", null, 2));

    updateUI();
}

//toy version of the observer pattern
function updateUI()
{
    document.getElementById("undo").disabled = !hist.canUndo();
    document.getElementById("redo").disabled = !hist.canRedo();
}

//our undo/redo helper class
var hist = new History();

function undo(event)
{
    hist.undoCmd()
}
function redo(event)
{
    hist.redoCmd()
}

//attach all functions to html elements
window.onload = function() {
    document.getElementById("DefaultHead").onclick = BodyEvent;
    document.getElementById("PirateHead").onclick = BodyEvent;
    document.getElementById("LepHead").onclick = BodyEvent;

    document.getElementById("DefaultLArm").onclick = BodyEvent;
    document.getElementById("PirateLArm").onclick = BodyEvent;
    document.getElementById("LepLArm").onclick = BodyEvent;

    document.getElementById("DefaultBody").onclick = BodyEvent;
    document.getElementById("PirateBody").onclick = BodyEvent;
    document.getElementById("LepBody").onclick = BodyEvent;

    document.getElementById("DefaultRArm").onclick = BodyEvent;
    document.getElementById("PirateRArm").onclick = BodyEvent;
    document.getElementById("LepRArm").onclick = BodyEvent;

    document.getElementById("DefaultLegs").onclick = BodyEvent;
    document.getElementById("PirateLegs").onclick = BodyEvent;
    document.getElementById("LepLegs").onclick = BodyEvent;

    document.getElementById("Default").onclick = BodyEvent;
    document.getElementById("Pirate").onclick = BodyEvent;
    document.getElementById("Leprechaun").onclick = BodyEvent;

    document.getElementById("undo").onclick = undo;
    document.getElementById("redo").onclick = redo;

    updateUI();
}
