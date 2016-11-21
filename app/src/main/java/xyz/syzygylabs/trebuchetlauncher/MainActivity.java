package xyz.syzygylabs.trebuchetlauncher;

import android.app.Activity;
import android.content.Intent;
import android.provider.Settings;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import app.akexorcist.bluetotohspp.library.BluetoothSPP;
import app.akexorcist.bluetotohspp.library.BluetoothState;
import app.akexorcist.bluetotohspp.library.DeviceList;

public class MainActivity extends AppCompatActivity {
    BluetoothSPP bt = new BluetoothSPP(this);
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if(!bt.isBluetoothAvailable()) {
            // any command for bluetooth is not available
        }
        bt.setupService();
        bt.startService(BluetoothState.DEVICE_OTHER);
        Intent intent = new Intent(getApplicationContext(), DeviceList.class);
        startActivityForResult(intent, BluetoothState.REQUEST_CONNECT_DEVICE);

    }
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode == BluetoothState.REQUEST_CONNECT_DEVICE) {
            if(resultCode == Activity.RESULT_OK)
                bt.connect(data);
            setup();
        } else if(requestCode == BluetoothState.REQUEST_ENABLE_BT) {
            if(resultCode == Activity.RESULT_OK) {

                setup();
            } else {
                // Do something if user doesn't choose any device (Pressed back)
            }
        }
    }
    public void onStart() {
        super.onStart();
        if(!bt.isBluetoothEnabled()) {
            // Do somthing if bluetooth is disable
        } else {
            // Do something if bluetooth is already enable
        }
    }
    public void setup(){
        bt.setOnDataReceivedListener(new BluetoothSPP.OnDataReceivedListener() {
            public void onDataReceived(byte[] data, String message) {
                TextView acX = (TextView) findViewById(R.id.acX);
                TextView acY = (TextView) findViewById(R.id.acY);
                TextView acZ = (TextView) findViewById(R.id.acZ);
                TextView gyX = (TextView) findViewById(R.id.gyX);
                TextView gyY = (TextView) findViewById(R.id.gyY);
                TextView gyZ = (TextView) findViewById(R.id.gyZ);
                int gyXK = message.indexOf("A");
                int gyYK = message.indexOf("B");
                int gyZK = message.indexOf("C");
                int acXK = message.indexOf("D");
                int acYK = message.indexOf("E");
                int acZK = message.indexOf("F");
                int end = message.indexOf("G");

                gyX.setText("X:" + message.substring(gyXK+1,gyYK));
                gyY.setText("Y:" +message.substring(gyYK+1,gyZK));
                gyZ.setText("Z:" +message.substring(gyZK+1,acXK));
                acX.setText("X:" +message.substring(acXK+1,acYK));
                acY.setText("Y:" +message.substring(acYK+1,acZK));
                acZ.setText("Z:" +message.substring(acZK+1,end));

                Log.e("TIZ", message);
            }
        });

        Button btnSend = (Button) findViewById(R.id.button);
        btnSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bt.send("1", true);
            }
        });
        Button btnRed = (Button) findViewById(R.id.btnGreen);
        Button btnBlue = (Button) findViewById(R.id.btnBlue);
        btnRed.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bt.send("2", true);
            }
        });

        btnBlue.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bt.send("3", true);
            }
        });
        Button btnClear = (Button) findViewById(R.id.btnCLear);
        btnClear.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bt.send("4", true);
            }
        });
    }

}
