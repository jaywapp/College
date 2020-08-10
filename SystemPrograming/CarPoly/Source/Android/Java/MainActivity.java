package com.test.test;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Looper;
import android.os.StrictMode;
import android.support.v7.app.AlertDialog;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import android.widget.ViewFlipper;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;
import org.xmlpull.v1.XmlPullParserFactory;

import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.List;
//Login 화면
public class MainActivity extends Activity {
    ViewFlipper Vf;
    EditText edit_phonenumber; //전화번호 입력
    EditText edit_password; // 비밀번호 입력
    Button btn_login; //Login 시도
    Button btn_join; //회원가입으로 전환
    // 서버와의 통신을 위한 class
    HttpPost httppost;
    HttpResponse response;
    HttpClient httpclient;
    List<NameValuePair> nameValuePairs;
    ProgressDialog dialog = null;
    //string buffer
    static String temp = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
        btn_login = (Button) findViewById(R.id.login);
        btn_join = (Button) findViewById(R.id.join);
        edit_phonenumber = (EditText) findViewById(R.id.phonenumber);
        edit_phonenumber.setNextFocusDownId(R.id.password);
        edit_password = (EditText) findViewById(R.id.password);
        edit_password.setNextFocusDownId(R.id.join);
    }

    public void onClick(View view) {
        Intent intent_join = new Intent(this, JoinActivity.class);
        switch (view.getId()) {
            case R.id.login: //Login 시도
                dialog = ProgressDialog.show(MainActivity.this, "", "Validating user...", true);
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        Looper.prepare();
                        try {
                            login();
                        } catch (IOException e1) {
                            e1.printStackTrace();
                        }
                        Looper.loop();
                    }
                }).start();
                break;
            case R.id.join://회원가입
                startActivity(intent_join);
                break;
        }
    }//onClick


    //Login 시 서버와의 data 송수신을 위한 함수
    void login() throws IOException {

        httpclient = new DefaultHttpClient();
        httppost = new HttpPost("http://152.149.43.194/logcheck.php"); //서버상 php 파일에 접근
        String phone = edit_phonenumber.getText().toString();
        String pw = edit_password.getText().toString();
        nameValuePairs = new ArrayList<NameValuePair>(2);
        nameValuePairs.add(new BasicNameValuePair("phone", phone)); //서버에 전달할 인자
        nameValuePairs.add(new BasicNameValuePair("pw", pw)); //서버에 전달할 인자
        httppost.setEntity(new UrlEncodedFormEntity(nameValuePairs));
        response = httpclient.execute(httppost);
        ResponseHandler<String> responseHandler = new BasicResponseHandler();
        final String response = httpclient.execute(httppost, responseHandler); //전달한 인자로 서버로부터 받은 값

        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                dialog.dismiss();
            }
        });
        if (!response.equalsIgnoreCase("0")) { //성공시
            runOnUiThread(new Runnable() {
                @Override
                public void run() {Toast.makeText(MainActivity.this, "Login Success", Toast.LENGTH_SHORT).show();}
            });
            Intent intent_login = new Intent(this, menuActivity.UserActivity.class);
            intent_login.putExtra("Input Phone number", phone); //menuActivity 로 전달할 인자
            intent_login.putExtra("Input Password", pw);
            intent_login.putExtra("String",response);
            startActivity(intent_login);
            finish();
        } else {Toast.makeText(MainActivity.this, "Login Fail", Toast.LENGTH_SHORT).show();}
    }
    //회원 가입을 구현한 class
    public static class JoinActivity extends Activity {

        HttpPost httppost;
        HttpResponse response;
        HttpClient httpclient;
        List<NameValuePair> nameValuePairs;
        ProgressDialog dialog = null;
        final Context context = this;
        //회원 가입시 입력받을 내용
        EditText editName;
        EditText editPhoneNumber;
        EditText editPassword;
        EditText editCarNumber;
        EditText editCarName;
        EditText editBohum;
        Button btnJoin;
        Button btnBack;
        Button btnBohum;
        int check = -1;
        private static final String SERVER_ADDRESS = "http://152.149.43.194"; //?????? ????

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_join);
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
            StrictMode.setThreadPolicy(policy);
            btnJoin = (Button) findViewById(R.id.btn_join);
            btnBack = (Button) findViewById(R.id.btn_back);
            btnBohum = (Button) findViewById(R.id.btn_bohum);
            editName = (EditText) findViewById(R.id.edit_name);
            editName.setNextFocusDownId(R.id.edit_phoneNumber);
            editPhoneNumber = (EditText) findViewById(R.id.edit_phoneNumber);
            editPhoneNumber.setNextFocusDownId(R.id.edit_password);
            editPassword = (EditText) findViewById(R.id.edit_password);
            editPassword.setNextFocusDownId(R.id.edit_carNumber);
            editCarNumber = (EditText) findViewById(R.id.edit_carNumber);
            editCarNumber.setNextFocusDownId(R.id.edit_carName);
            editCarName = (EditText) findViewById(R.id.edit_carName);
            editCarName.setNextFocusDownId(R.id.btn_bohum);
        }

        public void onClick(View v) {

            switch (v.getId()) {

                case R.id.btn_join: // 회원 가입 시도
                    //입력한 내용이 없을때
                    if (editName.getText().toString().equals("") || editPhoneNumber.getText().toString().equals("") || editPassword.getText().toString().equals("") || editCarName.getText().toString().equals("") || editCarNumber.getText().toString().equals("") || temp.equals("")) {
                        Toast.makeText(JoinActivity.this, "There are empty. Retry!", Toast.LENGTH_SHORT).show();
                        return;
                    }
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            String name = editName.getText().toString();
                            String phone = editPhoneNumber.getText().toString();
                            String pw = editPassword.getText().toString();
                            String carnumber = editCarNumber.getText().toString();
                            String carname = editCarName.getText().toString();
                            String bohum = temp;
                            try {
                                //중복된 전화번호 check
                                checkUser(phone, carnumber);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                            if (check == -1) { // Phone number, car number 중복상황
                                Toast.makeText(JoinActivity.this, "Phone number or Car Number is duplicate. Retry!", Toast.LENGTH_SHORT).show();
                                return;
                            }
                            check = -1;
                            try {
                                //회원가입 인자 전달,
                                URL url = new URL(SERVER_ADDRESS + "/joincheck.php?" + "name=" + URLEncoder.encode(name, "UTF-8") + "&phone=" + URLEncoder.encode(phone, "UTF-8") + "&pw=" + URLEncoder.encode(pw, "UTF-8") + "&carnum=" + URLEncoder.encode(carnumber, "UTF-8") + "&carname=" + URLEncoder.encode(carname, "UTF-8") + "&insu=" + URLEncoder.encode(bohum, "UTF-8") +"&permit=" +"1");
                                url.openStream();
                                String result = getXmlData("insertresult.xml", "result");
                                if (result.equals("1")) {
                                    Toast.makeText(JoinActivity.this, "Success! Do login", Toast.LENGTH_SHORT).show();
                                    editName.setText("");
                                    editPhoneNumber.setText("");
                                    editPassword.setText("");
                                    editCarName.setText("");
                                    editCarNumber.setText("");
                                    startActivity(new Intent(JoinActivity.this, MainActivity.class));
                                    finish();
                                } else
                                    Toast.makeText(JoinActivity.this, "Error!", Toast.LENGTH_SHORT).show();

                            } catch (MalformedURLException e) {
                                e.printStackTrace();
                            } catch (UnsupportedEncodingException e) {
                                e.printStackTrace();
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                        }

                    });
                    temp = "";
                    break;
                case R.id.btn_back:
                    //Login 화면으로 전환
                    finish();
                    break;
                case R.id.btn_bohum:
                    //회원 가입시 보험사 선택 창
                    final String item[] = {"삼성화재애니카", "현대해상하이카", "동부화재프로미", "LIG손해보험"};
                    AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(context);
                    alertDialogBuilder.setTitle("보험사를 선택해주세요.!");
                    alertDialogBuilder.setItems(item, new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int id) {
                            Toast.makeText(getApplicationContext(), item[id] + " is selected.", Toast.LENGTH_SHORT).show();
                            dialog.dismiss();
                            switch (item[id])
                            {
                                case "삼성화재애니카" :
                                    temp = "1";
                                    break;
                                case "현대해상하이카" :
                                    temp = "2";
                                    break;
                                case "동부화재프로미" :
                                    temp = "3";
                                    break;
                                case "LIG손해보험" :
                                    temp = "4";
                                    break;
                            }
                        }
                    });
                    AlertDialog alertDialog = alertDialogBuilder.create();
                    alertDialog.show();
                    break;
            }
        }

        //DB 서버와 통신할 때 필요한 함수
        static String getXmlData(String filename, String str) {
            String rss = SERVER_ADDRESS + "/";
            String ret = "";

            try {
                XmlPullParserFactory factory = XmlPullParserFactory.newInstance();
                factory.setNamespaceAware(true);
                XmlPullParser xpp = factory.newPullParser();
                URL server = new URL(rss + filename);
                InputStream is = server.openStream();
                xpp.setInput(is, "UTF-8");
                int eventType = xpp.getEventType();
                while (eventType != XmlPullParser.END_DOCUMENT) {
                    if (eventType == XmlPullParser.START_TAG) {
                        if (xpp.getName().equals(str)) {
                            ret = xpp.nextText();
                        }
                    }
                    eventType = xpp.next();
                }
            } catch (XmlPullParserException e) {
                e.printStackTrace();
            } catch (MalformedURLException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return ret;
        }
        /*중복 체크시 사용할 함수*/
        private void checkUser(String num, String car_num) throws IOException {
            httpclient = new DefaultHttpClient();
            httppost = new HttpPost("http://152.149.43.194/duplicationcheck.php");
            nameValuePairs = new ArrayList<NameValuePair>(2);
            nameValuePairs.add(new BasicNameValuePair("phone", num));
            nameValuePairs.add(new BasicNameValuePair("car_num", car_num));
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
}