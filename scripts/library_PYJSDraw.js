
var LibraryPYJS_Draw = {
    
    $PYJS_Draw__deps: [],

    $PYJS_Draw: {
        
        _defaults: {
            _width: 680,
            _height: 420
        },

        _fps: 45,
        _timerDelay: 70,
        _running: false,
        _displayCanvas: null,
        _workCanvas: null,
        _id: "PYJS_Draw_Canvas",

        
        // Taken from following web page
        // http://stackoverflow.com/questions/55677/how-do-i-get-the-
        // coordinates-of-a-mouse-click-on-a-canvas-element
        getMouseCoords: function(evt){

            var totalOffsetX = 0;
            var totalOffsetY = 0;
            var canvasX = 0;
            var canvasY = 0;
            var currentElement = PYJS_Draw._displayCanvas;

            do{
                    totalOffsetX += currentElement.offsetLeft;
                    totalOffsetY += currentElement.offsetTop;
            }
            while (currentElement = currentElement.offsetParent);

            canvasX = evt.pageX - totalOffsetX;
            canvasY = evt.pageY - totalOffsetY;

            // Fix for variable canvas width
            canvasX = Math.round( canvasX * (PYJS_Draw._displayCanvas.width 
                                     / PYJS_Draw._displayCanvas.offsetWidth) );
            canvasY = Math.round( canvasY * (PYJS_Draw._displayCanvas.height 
                                    / PYJS_Draw._displayCanvas.offsetHeight) );

            return {x:canvasX, y:canvasY};

        },


        // Taken from the following web page
        // http://unixpapa.com/js/mouse.html
        // 0 for left
        // 1 for middle
        // 2 for right
        getButton: function(evt){
        
            var button = null;

            if (evt.which == null)
                /* IE case */
                button= (evt.button < 2) ? 0 : ((evt.button == 4) ?  1 : 2);
            else
                /* All others */
                button= (evt.which < 2) ? 0 :  ((evt.which == 2) ? 1 : 2);

            return button;
        },
        
        
        mouseButtonDownCb: function(evt, id, cb){

            // Find out the mouse coordinates
            var mouseCoords = PYJS_Draw.getMouseCoords(evt);

            // Find out which button is down
            var button = PYJS_Draw.getButton(evt);

            // Call callback
            FUNCTION_TABLE[cb](id, mouseCoords.x, mouseCoords.y, button);
        },

        
        mouseMoveCb: function(evt, id, cb){

            // Find out the mouse coordinates
            var mouseCoords = PYJS_Draw.getMouseCoords(evt);

            // Call callback
            FUNCTION_TABLE[cb](id, mouseCoords.x, mouseCoords.y);
        },


        mouseButtonUpCb: function(evt, id, cb){

            // Find out the mouse coordinates
            var mouseCoords = PYJS_Draw.getMouseCoords(evt);

            // Find out which button is down
            var button = PYJS_Draw.getButton(evt);

            // Call callback
            FUNCTION_TABLE[cb](id, mouseCoords.x, mouseCoords.y, button);
        },

        
        quitCb: function(evt, id, cb){

            // Call callback
            FUNCTION_TABLE[cb](id);
        },


        timerCb: function(id, cb){
            
            if (PYJS_Draw._timerDelay != 0){
                setTimeout(function() { 
                        PYJS_Draw.timerCb(id, cb);
                    },PYJS_Draw._timerDelay);
            
            // Call callback
            FUNCTION_TABLE[cb](id);
            }
        },


        doLoop: function(){
            
            // If PYJS_Draw is in initialized state and _running is true then loop.
            if( PYJS_Draw._displayCanvas != null && PYJS_Draw._running){
               
                setTimeout(function() {
                    requestAnimFrame(PYJS_Draw.doLoop); 

                    // Copy from _workBuffer to _displayBuffer
                    var displayCtx = PYJS_Draw._displayCanvas.getContext("2d");
                    displayCtx.drawImage(PYJS_Draw._workCanvas, 0, 0);
                
                }, 1000 / PYJS_Draw._fps);
            }
        }
    },


    PYJS_Draw_init: function(){
        
        // If PYJS_Draw has not been initialized before, then initialize it. 
        // Else log it??
        if( PYJS_Draw._displayCanvas == null){
            
            // Create canvas, set its id, height and length, add to HTML body
            PYJS_Draw._displayCanvas = document.createElement("canvas");
            PYJS_Draw._displayCanvas.id = PYJS_Draw._id;
            PYJS_Draw._displayCanvas.height = PYJS_Draw._defaults._height;
            PYJS_Draw._displayCanvas.width = PYJS_Draw._defaults._width;
            
            PYJS_Draw._workCanvas = document.createElement("canvas");
            PYJS_Draw._workCanvas.height = PYJS_Draw._defaults._height;
            PYJS_Draw._workCanvas.width = PYJS_Draw._defaults._width;

            document.body.appendChild(PYJS_Draw._displayCanvas);
       
            window.requestAnimFrame = (function(){
	    return  window.requestAnimationFrame       ||
		    window.webkitRequestAnimationFrame ||
		    window.mozRequestAnimationFrame    ||
		    function( callback ){
		        window.setTimeout(callback, 1000 / 60);
		    };
	    })();
 
        }
        else{
            console.log("PYJS_Draw already initialized. Init call ignored");
        }
    },


    PYJS_Draw_cleanup: function(){

        // If PYJS_Draw is in initialized state, clean it. Else log it??
        if( PYJS_Draw._displayCanvas != null){
            
	    // We are doing nothing here as in python and sdl, loop() call is
	    // blocking and thus cleanup will be called only at quit.
	    // Here the loop() call is not blocking. It can't be blocking
            // as browser window actions to happen in this thread.
            //
            // But this is alright as the browser will do automatic cleanup 
            // at window close.
	    //
            // Stop loop if it is running
            // PYJS_Draw._running = false; 
            
            // Remove canvas from body, delete it
            // document.body.removeChild(PYJS_Draw._displayCanvas);
            
            // PYJS_Draw._timerDelay = 0;
            // delete PYJS_Draw._displayCanvas;
            // delete PYJS_Draw._workCanvas;

            // PYJS_Draw._displayCanvas = null;
            // PYJS_Draw._workCanvas = null;

        }
        else {
            console.log("PYJS_Draw not initialized. Cleanup call ignored");
        }
    },


    PYJS_Draw_beginPath: function(){

        // If PYJS_Draw is in initialized state, begin path. Else log it??
        if( PYJS_Draw._displayCanvas != null){
            
            // Call canvas's beginPath
            var ctx = PYJS_Draw._workCanvas.getContext("2d");
            ctx.beginPath();
       
       }
        else {
            console.log("PYJS_Draw not initialized. Cannot draw image");
        }
    },


    PYJS_Draw_strokeStyle: function(r, g, b, a){
        
        // If PYJS_Draw is in initialized state, set color. Else log it??
        if( PYJS_Draw._displayCanvas != null){
            
            // Call canvas's strokeStyle
            var ctx = PYJS_Draw._workCanvas.getContext("2d");
            var alpha = a/255;
            ctx.strokeStyle = "rgba(" + r.toString() + "," + g.toString() + "," + 
                                  b.toString() + "," +  alpha.toString() + ")";
       }
        else {
            console.log("PYJS_Draw not initialized. Cannot draw image");
        }
    },

    
    PYJS_Draw_lineWidth: function(w){

        // If PYJS_Draw is in initialized state, set line width. Else log it??
        if( PYJS_Draw._displayCanvas != null){

            // Call canvas's lineWidth
            var ctx = PYJS_Draw._workCanvas.getContext("2d");
            ctx.lineWidth = w;
        
        }
        else {
            console.log("PYJS_Draw not initialized. Cannot draw image");
        }
    },


    PYJS_Draw_moveTo: function(x, y){

        // If PYJS_Draw is in initialized state, move to point. Else log it??
        if( PYJS_Draw._displayCanvas != null){

            // Call canvas's moveTo function
            var ctx = PYJS_Draw._workCanvas.getContext("2d");
            ctx.moveTo(x,y);
       
       }
        else {
            console.log("PYJS_Draw not initialized. Cannot draw image");
        }
    },
   
    
    PYJS_Draw_lineTo: function(x, y){

        // If PYJS_Draw is in initialized state, make line. Else log it??
        if( PYJS_Draw._displayCanvas != null){
            
            // Call canvas's lineTo function
            var ctx = PYJS_Draw._workCanvas.getContext("2d");
            ctx.lineTo(x,y);
       
       }
        else {
            console.log("PYJS_Draw not initialized. Cannot draw image");
        }
    },


    PYJS_Draw_arc: function(x, y, r, sAngle, eAngle){

        // If PYJS_Draw is in initialized state, make arc. Else log it??
        if( PYJS_Draw._displayCanvas != null){
            
            // Call canvas's arc function
            var ctx = PYJS_Draw._workCanvas.getContext("2d");
            ctx.arc(x, y, r, sAngle, eAngle);
       
       }
        else {
            console.log("PYJS_Draw not initialized. Cannot draw image");
        }
    },


    PYJS_Draw_stroke: function(){

        // If PYJS_Draw is in initialized state, do stroke. Else log it??
        if( PYJS_Draw._displayCanvas != null){
            
            // Call canvas's stroke function
            var ctx = PYJS_Draw._workCanvas.getContext("2d");
            ctx.stroke();

        }
        else {
            console.log("PYJS_Draw not initialized. Cannot draw image");
        }
    },


    PYJS_Draw_loop: function(){

        // If PYJS_Draw is in initialized state set _running as true and 
        // requestAnimationFrame. Else log it.
        if( PYJS_Draw._displayCanvas != null){

            PYJS_Draw._running = true;
            requestAnimFrame(PYJS_Draw.doLoop); 
        }
    },


    PYJS_Draw_stop: function(){
   
        // Set _running as false;
        PYJS_Draw._running = false;
    },


    PYJS_Draw_clearRect: function(){
   
        // If PYJS_Draw is in initialized state, do paint. Else log it??
        if( PYJS_Draw._displayCanvas != null){
            
            var workCtx = PYJS_Draw._workCanvas.getContext("2d");
            var strokeStyle = workCtx.strokeStyle;
            workCtx.beginPath();
            workCtx.rect(0, 0,  PYJS_Draw._workCanvas.width,  
                                                PYJS_Draw._workCanvas.height);
            workCtx.fillStyle = 'white';
            workCtx.fill();
            workCtx.lineWidth = 1;
            workCtx.strokeStyle = 'white';
            workCtx.stroke();
            workCtx.strokeStyle = strokeStyle;
        }
        else {
            console.log("PYJS_Draw not initialized. Cannot draw image");
        }
    },


    PYJS_Draw_paint: function(){
  
        //Do nothing
    },


    PYJS_Draw_setTimerDelay: function(delay){
       
        // If PYJS_Draw is in initialized state, set timer delay. Else log it.
        if( PYJS_Draw._displayCanvas != null){

            PYJS_Draw._timerDelay = delay;
        }
    
    },


    PYJS_Draw_connectTimerCallback: function(id, cb)
    {
        // If PYJS_Draw is in initialized state connect the callback
        // else log it
        if( PYJS_Draw._displayCanvas != null){

            setTimeout(function() { 
                            PYJS_Draw.timerCb(id, cb);
                    },PYJS_Draw._timerDelay);
        }
         else {
            console.log("PYJS_Draw not initialized. Cannot add callback");
        }
    },


    PYJS_Draw_connectMouseButtonDownCallback: function(id, cb)
    {
        // If PYJS_Draw is in initialized state connect the callback
        // else log it
        if( PYJS_Draw._displayCanvas != null){

            PYJS_Draw._displayCanvas.addEventListener("mousedown",
                    function(evt) { // Cross browser compatable event functor
                        if (!evt) // i.e. the argument is undefined or null
                            evt = window.event;
                            PYJS_Draw.mouseButtonDownCb (evt, id, cb);
                    },false);
        }
         else {
            console.log("PYJS_Draw not initialized. Cannot add callback");
        }
   
    },


    PYJS_Draw_connectMouseMoveCallback: function(id, cb)
    {
        // If PYJS_Draw is in initialized state connect the callback
        // else log it
        if( PYJS_Draw._displayCanvas != null){

            PYJS_Draw._displayCanvas.addEventListener("mousemove",
                    function(evt) { // Cross browser compatable event functor
                        if (!evt) // i.e. the argument is undefined or null
                            evt = window.event;
                            PYJS_Draw.mouseMoveCb (evt, id, cb);
                    },false);
        }
        else {
            console.log("PYJS_Draw not initialized. Cannot add callback");
        }
   
    },


    PYJS_Draw_connectMouseButtonUpCallback: function(id, cb)
    {
        // If PYJS_Draw is in initialized state connect the callback
        // else log it
        if( PYJS_Draw._displayCanvas != null){

            PYJS_Draw._displayCanvas.addEventListener("mouseup",
                    function(evt) { // Cross browser compatable event functor
                        if (!evt) // i.e. the argument is undefined or null
                            evt = window.event;
                            PYJS_Draw.mouseButtonUpCb (evt, id, cb);
                    },false);
        }
        else {
            console.log("PYJS_Draw not initialized. Cannot add callback");
        }
   
    },


    PYJS_Draw_connectQuitCallback: function(cb, id)
    {
        // If PYJS_Draw is in initialized state connect the callback
        // else log it
        if( PYJS_Draw._displayCanvas != null){

            PYJS_Draw._displayCanvas.addEventListener("beforeunload",
                    function(evt) { // Cross browser compatable event functor
                        if (!evt) // i.e. the argument is undefined or null
                            evt = window.event;
                            PYJS_Draw.quitCb (evt, id, cb);
                    },false);
        }
        else {
            console.log("PYJS_Draw not initialized. Cannot add callback");
        }
   
    },

}
autoAddDeps(LibraryPYJS_Draw, "$PYJS_Draw");
mergeInto(LibraryManager.library, LibraryPYJS_Draw);
