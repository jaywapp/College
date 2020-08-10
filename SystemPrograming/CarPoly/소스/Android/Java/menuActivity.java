package com.test.test;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;
import android.widget.Toast;

import org.apache.http.NameValuePair;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;

import static android.widget.Toast.LENGTH_LONG;

/**
 * Created by junyoung Park on 2015-05-13.
 */
public class menuActivity extends Activity {
    static HttpPost httppost;
    static HttpResponse response;
    static HttpClient httpclient;
    static List<NameValuePair> nameValuePairs;
    static String res = "";
    static int initial = -1;
    static String[][] carlist = new String[5][6];

    //Login한 사람의 정보
    static class User {
        User() {
            setName("");
            setPhonenum("");
            setPassword("");
        }

        public static String phonenum;
        public static String password;
        public static String name;

        public static void setName(String name) {
            User.name = name;
        }

        public static void setPassword(String password) {
            User.password = password;
        }

        public static void setPhonenum(String phonenum) {
            User.phonenum = phonenum;
        }
    }
    //Control할 차량의 정보
    static class Car {
        public static String number = "";
        public static String name = "";
        public static String per = "";
        public static String lock = "";
        public static int power = -1;
        public static String st = "";
        public static String et = "";
        public static int bohum = -1;

        Car() {
            setNumber("");
            setName("");
            setPer("");
            setBohum(-1);
            setLock("");
            setPower(-1);
        }

        public static void setNumber(String number) {
            Car.number = number;
        }

        public static void setName(String name) {
            Car.name = name;
        }

        public static void setPer(String per) {
            Car.per = per;
        }

        public static void setSt(String date) {
            Car.st = date;
        }

        public static void setEt(String et) {
            Car.et = et;
        }

        public static void setBohum(int bohum) {
            Car.bohum = bohum;
        }

        public static void setLock(String lock) {
            Car.lock = lock;
        }

        public static void setPower(int power) {
            Car.power = power;
        }
    }

    static User user;
    static Car car;
    //내정보 class
    public static class UserActivity extends Activity {
        TextView username;
        TextView userphone;
        final Context context = this;

        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_user);
            if (initial == -1) {
                //선택할 차량 목록을 받아오기위한 변수 초기화
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 6; j++) {
                        carlist[i][j] = "";
                    }
                }

                Intent intent = getIntent();

                //mainActivity로 부터 정보를 받아옴
                user.setPhonenum(intent.getStringExtra("Input Phone number"));
                user.setPassword(intent.getStringExtra("Input Password"));
                res = intent.getStringExtra("String");
                if (res == "") { //최초 1회 data 받아오기
                } else {
                    cutString(res); // 받아온 정보 user와 car에 대입
                }
                int k = 0;
                while (carlist[k][0] != "") {
                    k++;
                }
                String[] item = new String[k];
                for (int j = 0; j < k; j++) {
                    item[j] = carlist[j][0];
                }


                AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(context);
                alertDialogBuilder.setTitle("Select Car!");
                alertDialogBuilder.setItems(item, new DialogInterface.OnClickListener() {
                //차량 선택
                    public void onClick(DialogInterface dialog, int id) {
                        //Toast.makeText(getApplicationContext(), item[id] + " is selected.", Toast.LENGTH_SHORT).show();
                        dialog.dismiss();
                        car.setNumber(carlist[id][0]);
                        car.setName(carlist[id][1]);
                        car.setPer(carlist[id][2]);
                        car.setSt(carlist[id][3]);
                        car.setEt(carlist[id][4]);
                        car.setLock(carlist[id][5]);
                        //car class에 다른 변수값 받아오기

                        Toast.makeText(getApplicationContext(), car.number + " is selected.", Toast.LENGTH_SHORT).show();
                    }

                });
                AlertDialog alertDialog = alertDialogBuilder.create();
                alertDialog.show();
                initial = 0;
            }
            //table 출력
            username = (TextView) findViewById(R.id.username);
            userphone = (TextView) findViewById(R.id.userphone);
            username.setText(user.name);
            userphone.setText(user.phonenum);
            TableLayout carTable = (TableLayout) findViewById(R.id.table_car);
            int i = 0;
            String temp = null;
            while (carlist[i][0] != "") {
                TableRow tr = new TableRow(this);
                TextView carmodel = new TextView(this);
                TextView carnumber = new TextView(this);
                TextView carpermit = new TextView(this);
                carmodel.setText(carlist[i][1]);
                carnumber.setText(carlist[i][0]);
                switch (carlist[i][2]) {
                    case "1":
                        temp = "Owner";
                        break;
                    case "0":
                        temp = "Guest";
                        break;
                }
                carpermit.setText(temp);
                temp = null;
                carmodel.setTextColor(Color.parseColor("#FFFFFF"));
                carnumber.setTextColor(Color.parseColor("#FFFFFF"));
                carpermit.setTextColor(Color.parseColor("#FFFFFF"));
                carmodel.setTextSize(TypedValue.COMPLEX_UNIT_PT, 10);
                carnumber.setTextSize(TypedValue.COMPLEX_UNIT_PT, 10);
                carpermit.setTextSize(TypedValue.COMPLEX_UNIT_PT, 10);
                tr.addView(carmodel);
                tr.addView(carnumber);
                tr.addView(carpermit);
                carTable.addView(tr);
                i++;
            }

        }

        void cutString(String response) {
            StringTokenizer st = new StringTokenizer(response, "@");
            user.setName(st.nextToken());
            String[] array = new String[st.countTokens()];
            int i = 0;
            while (st.hasMoreElements()) {
                array[i] = st.nextToken();
                StringTokenizer at = new StringTokenizer(array[i], "/");
                int j = 0;
                while (at.hasMoreElements()) {
                    carlist[i][j] = at.nextToken();
                    j++;
                }
                i++;
            }
        }

        public void onClick(View view) throws IOException {
            Intent intent_user = new Intent(this, UserActivity.class);
            Intent intent_stats = new Intent(this, StatsActivity.class);
            Intent intent_auth = new Intent(this, AuthActivity.class);
            Intent intent_locking = new Intent(this, LockingActivity.class);
            Intent intent_login = new Intent(this, MainActivity.class);
            switch (view.getId()) {

                case R.id.myinfor:
                    startActivity(intent_user); //내정보 메뉴
                    finish();
                    break;
                case R.id.stats:
                    startActivity(intent_stats); //사용내역 메뉴
                    finish();
                    break;
                case R.id.auth:
                    startActivity(intent_auth); // 권한관련 메뉴
                    finish();
                    break;
                case R.id.lock:
                    startActivity(intent_locking); //Door control메뉴
                    finish();
                    break;
                case R.id.logout:// logout
                    if (logout().equals("1"))
                        Toast.makeText(this, "Logout Success!", Toast.LENGTH_SHORT).show();
                    else
                        break;
                    finish();
                    startActivity(intent_login);
                    break;
            }

        }
    }

    /**
     * Created by junyoung Park on 2015-05-09.
     */
    // 사용내역 메뉴
    public static class StatsActivity extends Activity {
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_stats);
            TableLayout statsTable = (TableLayout) findViewById(R.id.table_stats);
            TableRow tr = new TableRow(this);
            TextView start = new TextView(this);
            TextView end = new TextView(this);
            start.setText(car.st);
            end.setText(car.et);
            end.setGravity(Gravity.CENTER);
            start.setGravity(Gravity.CENTER);
            start.setTextColor(Color.parseColor("#FFFFFF"));
            end.setTextColor(Color.parseColor("#FFFFFF"));
            start.setTextSize(TypedValue.COMPLEX_UNIT_PT, 10);
            end.setTextSize(TypedValue.COMPLEX_UNIT_PT, 10);
            tr.addView(start);
            tr.addView(end);
            statsTable.addView(tr);
        }

        public void onClick(View view) throws IOException {
            Intent intent_user = new Intent(this, UserActivity.class);
            Intent intent_stats = new Intent(this, StatsActivity.class);
            Intent intent_auth = new Intent(this, AuthActivity.class);
            Intent intent_locking = new Intent(this, LockingActivity.class);
            Intent intent_login = new Intent(this, MainActivity.class);
            switch (view.getId()) {
                case R.id.myinfor:
                    startActivity(intent_user);//내정보메뉴
                    finish();
                    break;
                case R.id.stats:
                    startActivity(intent_stats); //사용내역 메뉴
                    finish();
                    break;
                case R.id.auth:
                    startActivity(intent_auth); //권한메뉴
                    finish();
                    break;
                case R.id.lock:
                    startActivity(intent_locking); //Door control 메뉴
                    finish();
                    break;
                case R.id.logout: // logout
                    if (logout().equals("1"))
                        Toast.makeText(this, "Logout Success!", Toast.LENGTH_SHORT).show();
                    else
                        break;
                    finish();
                    startActivity(intent_login);
                    break;
            }
        }
    }

    /**
     * Created by junyoung Park on 2015-05-09.
     */

    // Door control class
    public static class LockingActivity extends Activity {
        ImageView state;
        URL url = null;
        private static final String SERVER_ADDRESS = "http://152.149.43.194";

        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_locking);

            // lock 상태확인 후 동기화
            state = (ImageView) findViewById(R.id.state);
            if (car.lock == "1") {
                state.setImageResource(R.drawable.locked);
            } else {
                state.setImageResource(R.drawable.unlocked);
            }

        }
        //변경할 lock상태 전송
        String sendlock() throws IOException {

            httpclient = new DefaultHttpClient();
            httppost = new HttpPost("http://152.149.43.194/lock.php");
            nameValuePairs = new ArrayList<NameValuePair>(2);
            nameValuePairs.add(new BasicNameValuePair("carnum", car.number));
            nameValuePairs.add(new BasicNameValuePair("lock", car.lock));
            httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
            response = httpclient.execute(httppost);
            ResponseHandler<String> responseHandler = new BasicResponseHandler();
            final String response = httpclient.execute(httppost, responseHandler);
            return response;
        }
        //상태변경을 위한 함수
        void changeState() throws IOException {
            if (car.lock == "1") {
                car.setLock("0");
                state.setImageResource(R.drawable.unlocked);
                Toast.makeText(this, "Unlock", Toast.LENGTH_SHORT).show();
            } else {
                car.setLock("1");
                state.setImageResource(R.drawable.locked);
                Toast.makeText(this, "Lock", Toast.LENGTH_SHORT).show();
            }
            String temp = sendlock();
            if (temp.equals(car.lock)) {

            } else
                Toast.makeText(this, "Error about Lock state", Toast.LENGTH_SHORT).show();

        }

        public void onClick(View view) throws IOException {
            Intent intent_user = new Intent(this, UserActivity.class);
            Intent intent_stats = new Intent(this, StatsActivity.class);
            Intent intent_auth = new Intent(this, AuthActivity.class);
            Intent intent_login = new Intent(this, MainActivity.class);
            Intent intent_locking = new Intent(this, LockingActivity.class);
            switch (view.getId()) {
                case R.id.myinfor:
                    startActivity(intent_user); //내정보 메뉴
                    finish();
                    break;
                case R.id.stats:
                    startActivity(intent_stats); //사용내역 메뉴
                    finish();
                    break;
                case R.id.auth:
                    startActivity(intent_auth); //권한 메뉴
                    finish();
                    break;
                case R.id.lock:
                    startActivity(intent_locking);//Door control 메뉴
                    finish();
                    break;
                case R.id.state: //lock상태 변경
                    changeState();
                    break;
                case R.id.logout: // logout
                    if (logout().equals("1"))
                        Toast.makeText(this, "Logout Success!", Toast.LENGTH_SHORT).show();
                    else
                        break;
                    finish();
                    startActivity(intent_login);
                    break;

            }
        }
    }

    /**
     * Created by junyoung Park on 2015-05-09.
     */

    //권한 메뉴
    public static class AuthActivity extends Activity {
        String userList[][] = new String[5][2]; //이름 번호 권한
        private static final String SERVER_ADDRESS = "http://152.149.43.194";
        String temp = null;

        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_auth);
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 2; j++) {
                    userList[i][j] = "";
                }
            } //권한을 받아올 변수(재사용) 초기화
            try {
                getlist(); //목록 받아오기
            } catch (IOException e) {
                e.printStackTrace();
            }
            TableLayout permitTable = (TableLayout) findViewById(R.id.table_permit);
            int i = 0;
            //목록 출력
            while (!userList[i][0].equals("")) {
                TableRow tr = new TableRow(this);
                TextView usernumber = new TextView(this);
                TextView userpermit = new TextView(this);
                usernumber.setText(userList[i][0]);
                if (userList[i][1].equals("1"))
                    userpermit.setText("Owner");
                else
                    userpermit.setText("User");
                //userpermit.setText(userList[i][1]); // password라는 변수를 재활용, 사실 권한
                userpermit.setGravity(Gravity.CENTER);
                usernumber.setGravity(Gravity.CENTER);
                usernumber.setTextColor(Color.parseColor("#FFFFFF"));
                userpermit.setTextColor(Color.parseColor("#FFFFFF"));
                usernumber.setTextSize(TypedValue.COMPLEX_UNIT_PT, 10);
                userpermit.setTextSize(TypedValue.COMPLEX_UNIT_PT, 10);
                tr.addView(usernumber);
                tr.addView(userpermit);
                permitTable.addView(tr);
                i++;
            }


        }
        //목록을 받아오는 함수
        void getlist() throws IOException {

            httpclient = new DefaultHttpClient();
            httppost = new HttpPost("http://152.149.43.194/permitlist.php");
            nameValuePairs = new ArrayList<NameValuePair>(1);
            nameValuePairs.add(new BasicNameValuePair("carnum", car.number));
            httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
            response = httpclient.execute(httppost);
            ResponseHandler<String> responseHandler = new BasicResponseHandler();
            final String response = httpclient.execute(httppost, responseHandler);
            //Toast.makeText(this, "response" + response , Toast.LENGTH_SHORT).show();
            if (!response.equalsIgnoreCase("0")) {
                cutString(response);
            } else {
            }
        }

        void cutString(String response) {
            StringTokenizer st = new StringTokenizer(response, "@");
            st.nextToken();
            String[] array = new String[st.countTokens()];
            int i = 0;
            while (st.hasMoreElements()) {
                array[i] = st.nextToken();
                StringTokenizer at = new StringTokenizer(array[i], "/");
                int j = 0;
                while (at.hasMoreElements()) {
                    userList[i][j] = at.nextToken();
                    j++;
                }
                i++;
            }
        }

        public void onClick(View view) throws IOException {
            Intent intent_user = new Intent(this, UserActivity.class);
            Intent intent_stats = new Intent(this, StatsActivity.class);
            Intent intent_auth = new Intent(this, AuthActivity.class);
            Intent intent_locking = new Intent(this, LockingActivity.class);
            Intent intent_add = new Intent(this, AddUser.class);
            Intent intent_login = new Intent(this, MainActivity.class);
            switch (view.getId()) {
                case R.id.myinfor:
                    startActivity(intent_user); //내정보 메뉴
                    finish();
                    break;
                case R.id.stats:
                    startActivity(intent_stats); //사용내역 메뉴
                    finish();
                    break;
                case R.id.auth:
                    startActivity(intent_auth); //권한 관련 메뉴
                    finish();
                    break;
                case R.id.lock: //Door control 메뉴
                    startActivity(intent_locking);
                    finish();
                    break;
                case R.id.btn_add: //권한 추가
                    startActivity(intent_add);
                    break;
                case R.id.logout: // logout
                    if (logout().equals("1"))
                        Toast.makeText(this, "Logout Success!", Toast.LENGTH_SHORT).show();
                    else
                        break;
                    finish();
                    startActivity(intent_login);
                    break;
            }
        }
    }
    //권한 추가 메뉴 (Join과 비슷함)
    public static class AddUser extends Activity {

        EditText editName;
        EditText editPhoneNumber;
        EditText editPassword;
        Button btnAdd;
        Button btnBack;
        int check = -1;
        private static final String SERVER_ADDRESS = "http://152.149.43.194";

        public void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_add);

            btnAdd = (Button) findViewById(R.id.add);
            btnBack = (Button) findViewById(R.id.add_back);
            editName = (EditText) findViewById(R.id.edit_name);
            editName.setNextFocusDownId(R.id.edit_phoneNumber);
            editPhoneNumber = (EditText) findViewById(R.id.edit_phoneNumber);
            editPhoneNumber.setNextFocusDownId(R.id.edit_password);
            editPassword = (EditText) findViewById(R.id.edit_password);
            editPassword.setNextFocusDownId(R.id.btn_add);

        }

        public void onClick(View view) throws IOException {
            Intent intent_user = new Intent(this, UserActivity.class);
            Intent intent_stats = new Intent(this, StatsActivity.class);
            Intent intent_locking = new Intent(this, LockingActivity.class);
            final Intent intent_auth = new Intent(this, AuthActivity.class);
            Intent intent_login = new Intent(this, MainActivity.class);
            switch (view.getId()) {
                case R.id.add_back:
                    finish();
                    break;
                case R.id.add:
                    if (editName.getText().toString().equals("") || editPhoneNumber.getText().toString().equals("") || editPassword.getText().toString().equals("")) {
                        Toast.makeText(AddUser.this, "Retry!", Toast.LENGTH_SHORT).show();
                        return;
                    }
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            String name = editName.getText().toString();
                            String phone = editPhoneNumber.getText().toString();
                            String pw = editPassword.getText().toString();
                            try {
                                checkUser(phone, car.number);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            if (check == -1) {
                                Toast.makeText(AddUser.this, "Fail! Retry!", Toast.LENGTH_SHORT).show();
                                return;
                            }
                            check = -1;
                            try {
                                URL url = new URL(SERVER_ADDRESS + "/joincheck.php?" + "name=" + URLEncoder.encode(name, "UTF-8") + "&phone=" + URLEncoder.encode(phone, "UTF-8") + "&pw=" + URLEncoder.encode(pw, "UTF-8") + "&carnum=" + URLEncoder.encode(car.number, "UTF-8") + "&carname=" + URLEncoder.encode(car.name, "UTF-8") +  "&carnum=" + URLEncoder.encode(car.number, "UTF-8") + "&insu=" + URLEncoder.encode(Integer.toString(car.bohum), "UTF-8") + "&permit=" + "0");
                                url.openStream();
                                String result = MainActivity.JoinActivity.getXmlData("insertresult.xml", "result");
                                if (result.equals("1")) {
                                    Toast.makeText(AddUser.this, "Success!", Toast.LENGTH_SHORT).show();
                                    editName.setText("");
                                    editPhoneNumber.setText("");
                                    editPassword.setText("");
                                    finish();
                                } else
                                    Toast.makeText(AddUser.this, "Fail!", Toast.LENGTH_SHORT).show();
                            } catch (MalformedURLException e) {
                                e.printStackTrace();
                            } catch (UnsupportedEncodingException e) {
                                e.printStackTrace();
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                        }

                    });
                    break;
                case R.id.myinfor:
                    startActivity(intent_user);
                    finish();
                    break;
                case R.id.stats:
                    startActivity(intent_stats);
                    finish();
                    break;
                case R.id.auth:
                    finish();
                    break;
                case R.id.lock:
                    startActivity(intent_locking);
                    finish();
                    break;
                case R.id.logout:
                    if (logout().equals("1"))
                        Toast.makeText(this, "Logout Success!", Toast.LENGTH_SHORT).show();
                    else
                        break;
                    finish();
                    startActivity(intent_login);
                    break;
            }
        }

        private void checkUser(String num, String car_num) throws IOException {
            httpclient = new DefaultHttpClient();
            httppost = new HttpPost("http://152.149.43.194/duplicationcheck.php");
            nameValuePairs = new ArrayList<NameValuePair>(2);
            nameValuePairs.add(new BasicNameValuePair("phone", num));
            nameValuePairs.add(new BasicNameValuePair("carnum", car_num));
            httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
            response = httpclient.execute(httppost);
            ResponseHandler<String> responseHandler = new BasicResponseHandler();
            final String response = httpclient.execute(httppost, responseHandler);
            if (response.equalsIgnoreCase("User Found")) { //???
            } else {
                check = 1;
            }
        }
    }
    //logout함수
    static String logout() throws IOException {
        httpclient = new DefaultHttpClient();
        httppost = new HttpPost("http://152.149.43.194/logout.php");
        nameValuePairs = new ArrayList<NameValuePair>(2);
        nameValuePairs.add(new BasicNameValuePair("login", "0")); // Server속 login상태 변경
        nameValuePairs.add(new BasicNameValuePair("carnum", car.number));
        httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
        response = httpclient.execute(httppost);
        ResponseHandler<String> responseHandler = new BasicResponseHandler();
        final String response = httpclient.execute(httppost, responseHandler);
        return response;

    }

}