package com.example.j1studentconnect;

import androidx.appcompat.app.AppCompatActivity;
import androidx.cardview.widget.CardView;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;

public class MainActivity extends AppCompatActivity {

    private ImageButton btnSearch, btnProfile, btnCalendar,
                        btnCalendarHotkey, btnAvatar, btnX;

    CardView ConvenientCard;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ConstructButton();
        ClickButton();
        ConstructLayout();
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
                ConvenientCard.setVisibility(View.GONE);

            }
        });

    }

}