package electroscholars.com.accelerometer;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.EditText;
import android.hardware.SensorEventListener;
import android.hardware.SensorEvent;
import android.hardware.SensorManager;
import android.hardware.Sensor;

public class AccelerometerActivity extends AppCompatActivity {

    private static final CharSequence Title = "Accelerometer Reading Test";

    EditText xaxis_value;
    EditText yaxis_value;
    EditText zaxis_value;
    EditText xaxis_la_value;
    EditText yaxis_la_value;
    EditText zaxis_la_value;
    EditText magnitude_value;

    Sensor accelerometer;
    SensorManager accelerometer_manager;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_accelerometer);
        setTitle(this.Title);

        //Placeholders for EditTexts
        xaxis_value = (EditText) findViewById(R.id.xaxisTextEdit);
        yaxis_value = (EditText) findViewById(R.id.yaxisEditText);
        zaxis_value = (EditText) findViewById(R.id.zaxisEditText);

        xaxis_la_value = (EditText) findViewById(R.id.xaxisLAEditText);
        yaxis_la_value = (EditText) findViewById(R.id.yaxisLAEditText);
        zaxis_la_value = (EditText) findViewById(R.id.zaxisLAEditText);

        magnitude_value = (EditText) findViewById(R.id.magnitudeEditText);

        //Property changer
        xaxis_value.setFocusable(false);
        yaxis_value.setFocusable(false);
        zaxis_value.setFocusable(false);

        //Adds manager
        accelerometer_manager = (SensorManager) this.getSystemService(SENSOR_SERVICE);
        accelerometer = accelerometer_manager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        accelerometer_manager.registerListener(listener, accelerometer, SensorManager.SENSOR_DELAY_NORMAL);

    }

    //SensorEventListener object
    protected SensorEventListener listener = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent sensorEvent) {
            updateReading(sensorEvent);
            calculateLinearAcceleration(sensorEvent);
        }

        @Override
        public void onAccuracyChanged(Sensor sensor, int i) {
            //unused
        }
    };


    private void updateReading(SensorEvent event){
        float xaxis_force;
        float yaxis_force;
        float zaxis_force;

        xaxis_force = event.values[0];
        yaxis_force = event.values[1];
        zaxis_force = event.values[2];

        xaxis_value.setText(String.valueOf(xaxis_force));
        yaxis_value.setText(String.valueOf(yaxis_force));
        zaxis_value.setText(String.valueOf(zaxis_force));

        magnitude_value.setText(String.valueOf(Math.sqrt(Math.pow(xaxis_force, 2)) + Math.pow(yaxis_force, 2) + Math.pow(zaxis_force, 2)));
    }

    private void calculateLinearAcceleration(SensorEvent event){
        final float alpha = (float) 0.8;

        float[] gravity = {(float) 9.8, (float) 9.8, (float) 9.8};

        float[] linear_acceleration = {0, 0, 0};

        gravity[0] = alpha * gravity[0] + (1-alpha) * event.values[0];
        gravity[1] = alpha * gravity[1] + (1-alpha) * event.values[1];
        gravity[2] = alpha * gravity[2] + (1-alpha) * event.values[2];

        linear_acceleration[0] = event.values[0] - gravity[0];
        linear_acceleration[1] = event.values[1] - gravity[1];
        linear_acceleration[2] = event.values[2] - gravity[2];

        xaxis_la_value.setText(String.valueOf(linear_acceleration[0]));
        yaxis_la_value.setText(String.valueOf(linear_acceleration[1]));
        zaxis_la_value.setText(String.valueOf(linear_acceleration[2]));

    }



}
