package edu.sdsmt.fagrey_nathaniel.wumbus;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.view.View;

import androidx.annotation.Nullable;

public class MyGameView2 extends View {
    private Paint paintBlack;
    private Paint roomPaint;
    private Paint playerPaint;
    private Paint exitPaint;
    private float radius;
    private boolean circle;
    private boolean square;
    private boolean triangle;

    private Game game;

    private final float playerRadius = 25;

    public MyGameView2(Context context) {
        super(context);
        init(context);
    }

    private float DpToPixel(float dp){
        float pxPerDp = (float)getResources().getDisplayMetrics().densityDpi;
        pxPerDp = pxPerDp / DisplayMetrics.DENSITY_DEFAULT;

        return dp * pxPerDp;
    }

    public MyGameView2(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public MyGameView2(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    public MyGameView2(Context context, @Nullable AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        init(context);
    }

    public void SetPlayerShape(int val){
        if( val == 0)
            MakePlayerCircle();
        else if( val == 1)
            MakePlayerSquare();
        else
            MakePlayerTriangle();
    }

    private void MakePlayerCircle(){
        circle = true;
        square = false;
        triangle = false;
        update();
    }

    private void MakePlayerSquare(){
        circle = false;
        square = true;
        triangle = false;
        update();
    }

    private void MakePlayerTriangle() {
        circle = false;
        square = false;
        triangle = true;
        update();
    }

    public void setGame(Game game){
        this.game = game;
    }


    private void init(Context context){

        paintBlack = new Paint( Paint.ANTI_ALIAS_FLAG);
        playerPaint = new Paint();
        exitPaint = new Paint();
        roomPaint = new Paint();
        roomPaint.setColor(Color.GREEN);
        playerPaint.setColor(Color.RED);
        exitPaint.setColor(Color.YELLOW);
        circle = true;
        square = false;
        triangle = false;
    }

    public void update(){
        invalidate();
    }

    public void onDraw(Canvas canvas){

        radius = (float) ((float)(getWidth() / 4.0) / 2.0);

        int x = 0;
        int y = 0;

        for( int j = 1; j < 9; j += 2){
            x = 0;
            for( int i = 1; i < 9; i += 2 ){
                if( game.foundExit() && x == game.getExitPos()[0] && y == game.getExitPos()[1])
                    canvas.drawCircle(mapping(x), mapping(y), radius, exitPaint);

                else if( game.haveVisited(x , y) )
                    canvas.drawCircle(i * radius, j *radius, radius, paintBlack);

                else
                    canvas.drawCircle(i * radius, j *radius, radius, roomPaint);

                ++x;
            }

            ++y;
        }

        if( circle){
            canvas.drawCircle(mapping(game.getCharacterPos()[0]), mapping(game.getCharacterPos()[1]), radius/2, playerPaint);
        }


        else if( square ){
            drawSquare(canvas, playerPaint, mapping(game.getCharacterPos()[0]), mapping(game.getCharacterPos()[1]), (int)radius );
        }


        else if( triangle ){
            drawTriangle(canvas, playerPaint, mapping(game.getCharacterPos()[0]), mapping(game.getCharacterPos()[1]), (int)radius );
        }
    }

    public int mapping(int coord){
        return 2 * (int)radius * coord + (int)radius;
    }

    public void ChangeRoomColor(int color){
        roomPaint.setColor(color);
    }

    // Code taken from https://kylewbanks.com/blog/drawing-triangles-rhombuses-and-other-shapes-on-android-canvas#:~:text=Simply%20call%20drawTriangle%20with%20the,the%20width%20of%20the%20triangle.&text=Not%20bad%2C%20with%20a%20little,for%20your%20triangle%20drawing%20needs.
    private void drawTriangle(Canvas canvas, Paint paint, int x, int y, int width) {
        int halfWidth = width / 2;

        Path path = new Path();
        path.moveTo(x, y - halfWidth); // Top
        path.lineTo(x - halfWidth, y + halfWidth); // Bottom left
        path.lineTo(x + halfWidth, y + halfWidth); // Bottom right
        path.lineTo(x, y - halfWidth); // Back to Top
        path.close();

        canvas.drawPath(path, paint);
    }

    // Code modified from https://kylewbanks.com/blog/drawing-triangles-rhombuses-and-other-shapes-on-android-canvas#:~:text=Simply%20call%20drawTriangle%20with%20the,the%20width%20of%20the%20triangle.&text=Not%20bad%2C%20with%20a%20little,for%20your%20triangle%20drawing%20needs.
    private void drawSquare(Canvas canvas, Paint paint, int x, int y, int width){
        int halfWidth = width / 2;

        Path path = new Path();
        path.moveTo(x - halfWidth, y - halfWidth);
        path.lineTo(x + halfWidth, y - halfWidth);
        path.lineTo(x - halfWidth, y + halfWidth);

        path.moveTo(x + halfWidth, y + halfWidth); 
        path.lineTo(x + halfWidth, y - halfWidth);
        path.lineTo(x - halfWidth, y + halfWidth);
        path.close();

        canvas.drawPath(path, paint);

    }

    public int getRoomColor(){
        return roomPaint.getColor();
    }

    public int getPlayerShape(){
        if( circle)
            return 0;
        else if (square)
            return 1;
        else
            return 2;
    }
}
