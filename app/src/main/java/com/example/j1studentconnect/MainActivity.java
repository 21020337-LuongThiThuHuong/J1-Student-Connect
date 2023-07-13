package com.example.j1studentconnect;
//import State.*;

import androidx.appcompat.app.AppCompatActivity;
import androidx.cardview.widget.CardView;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;

import java.util.Calendar;

public class MainActivity extends AppCompatActivity {

    private ImageButton btnSearch, btnProfile, btnCalendar,
                        btnCalendarHotkey, btnAvatar, btnX;
    private Button btnRecover;
    private CardView ConvenientCard;
    private TextView txtToday;
    private Calendar today = Calendar.getInstance();
    public static boolean recover = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ConstructLayout();
        ConstructButton();
        ClickButton();
    }

    private void ConstructTextView(){

        //txtRecover = (TextView) findViewById(R.id.recover);
        txtToday = (TextView) findViewById(R.id.today);

    }

    private void RenderToday(){
        String date;
        date = today.get(Calendar.DATE) + " Tháng " + (today.get(Calendar.MONTH) + 1) + ", " + today.get(Calendar.YEAR);
        txtToday.setText(date);
    }

    private void ConstructButton(){

        btnSearch = (ImageButton) findViewById(R.id.homeSearch);
        btnProfile = (ImageButton) findViewById(R.id.homeProfile);
        btnCalendar = (ImageButton) findViewById(R.id.TimeTable);
        btnCalendarHotkey = (ImageButton) findViewById(R.id.calendarHotKey);
        btnAvatar = (ImageButton) findViewById(R.id.dogAvt);
        btnX = (ImageButton) findViewById(R.id.x);

    }

    private void ConstructLayout(){

        ConvenientCard = (CardView) findViewById(R.id.convenientNoti);
        btnRecover = (Button) findViewById(R.id.recover);
        if (recover == false) {

            ConstructTextView();
            RenderToday();
        }
        else {
            ConvenientCard.setVisibility(View.GONE);
            btnRecover.setVisibility(View.VISIBLE);
        }

    }

    private void ClickButton(){

        btnAvatar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MainActivity.this, ProfileActivity.class));
            }
        });

        btnCalendar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MainActivity.this, CalendarActivity.class));
            }
        });

        btnProfile.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MainActivity.this, ProfileActivity.class));
            }
        });
        btnSearch.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MainActivity.this, SearchActivity.class));
            }
        });

        btnCalendarHotkey.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MainActivity.this, CalendarActivity.class));
            }
        });

        btnX.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {

                if (recover == false){
                    recover = true;
                    ConvenientCard.setVisibility(View.GONE);
                    btnRecover.setVisibility(View.VISIBLE);
                }
            }
        });

        btnRecover.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                ConvenientCard.setVisibility(View.VISIBLE);
                btnRecover.setVisibility(View.GONE);
                recover = false;
            }
        });

    }

}