package com.example.j1studentconnect;

import android.content.Intent;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.os.Bundle;
import android.os.PersistableBundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class EditProfile extends AppCompatActivity {
    EditText name, email, phone;
    String user_name, user_id, user_email, user_phone;
    Button save;
    DatabaseReference reference;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit_profile);

        name = findViewById(R.id.edit_name);
        email = findViewById(R.id.edit_email);
        phone = findViewById(R.id.edit_phone_number);
        save = findViewById(R.id.btn_save_edit);

        Intent intentBefore = getIntent();
        user_name = intentBefore.getStringExtra("name");
        user_email = intentBefore.getStringExtra("email");
        user_id = intentBefore.getStringExtra("student_id");
        user_phone = intentBefore.getStringExtra("phone");

        name.setText(user_name);
        email.setText(user_email);
        phone.setText(user_phone);

        name.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) { }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) { }

            @Override
            public void afterTextChanged(Editable editable) {
                user_name = name.getText().toString();
                save.setEnabled(true);
                save.setBackgroundColor(Color.BLUE);
            }
        });

        email.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) { }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) { }

            @Override
            public void afterTextChanged(Editable editable) {
                user_email = email.getText().toString();
                save.setEnabled(true);
                save.setBackgroundColor(Color.BLUE);
            }
        });

        phone.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) { }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) { }

            @Override
            public void afterTextChanged(Editable editable) {
                user_phone = phone.getText().toString();
                save.setEnabled(true);
                save.setBackgroundColor(Color.BLUE);
            }
        });

        save.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Toast.makeText(EditProfile.this, "Cập nhật thành công!", Toast.LENGTH_SHORT).show();
                updateDatabase();
                finish();
            }
        });
    }

    public void updateDatabase() {
        reference = FirebaseDatabase.getInstance("https://j1-student-connect-default-rtdb.asia-southeast1.firebasedatabase.app/").getReference("1srn9ku9VkZvIf9dugTTPEcr2tRk3tkWl0MWxjzT1lp0").child("users").child(user_id);
        reference.child("name").setValue(user_name);
        reference.child("email").setValue(user_email);
        reference.child("phone").setValue(user_phone);
    }
}
