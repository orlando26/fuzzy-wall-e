package com.percepcion.fer.wall_e;

import android.content.Intent;
import android.speech.RecognizerIntent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.percepcion.fer.arduino.arduino;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private Button listenBtn;
    private Button btnConnect;
    private final int REQ_CODE_SPEECH_INPUT = 100;
    private arduino arduino;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        arduino = new arduino(this);

        listenBtn = (Button)findViewById(R.id.btnListen);
        listenBtn.setOnClickListener(this);
        btnConnect = (Button)findViewById(R.id.btnConnect);
        btnConnect.setOnClickListener(this);

    }

    @Override
    public void onClick(View view) {
        switch (view.getId()){
            case R.id.btnListen:
                Intent i = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
                i.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, "en-US");
                try {
                    startActivityForResult(i,REQ_CODE_SPEECH_INPUT);
                } catch (Exception e) {
                    Toast.makeText(this, "Error initializing speech to text engine.", Toast.LENGTH_LONG).show();
                }
                break;
            case R.id.btnConnect:
                arduino.connect();
                break;
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode==REQ_CODE_SPEECH_INPUT  && resultCode==RESULT_OK) {
            ArrayList<String> thingsYouSaid = data.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
            String palabra = "";
            for (String str: thingsYouSaid){
                if(str.equals("muy frío")){
                    palabra = str;
                    arduino.write(String.valueOf((char)10));
                    break;
                }else if(str.equals("frío")){
                    palabra = str;
                    arduino.write(String.valueOf((char)20));
                    break;
                }else if(str.equals("caliente")){
                    palabra = str;
                    arduino.write(String.valueOf((char)30));
                    break;
                }else if(str.equals("muy caliente")){
                    palabra = str;
                    arduino.write(String.valueOf((char)40));
                    break;
                }
            }
            ((TextView)findViewById(R.id.text)).setText(thingsYouSaid.get(0));
        }
        Intent i = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        i.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, "en-US");
        try {
            startActivityForResult(i,REQ_CODE_SPEECH_INPUT);
        } catch (Exception e) {
            Toast.makeText(this, "Error initializing speech to text engine.", Toast.LENGTH_LONG).show();
        }
    }

}
