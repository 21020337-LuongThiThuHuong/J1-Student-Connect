package com.example.j1studentconnect;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class RequestAdd extends AppCompatActivity {
    private Spinner spinner1;
    private Button attachButton;
    private static final int PICKFILE_REQUEST_CODE = 1;
    private String path;

    private TextView InfoAddRequest;
    private LinearLayout btnRequestProcessing;
    private ImageButton btnRHome, btnRSearch, btnRProfile;

    DatabaseReference reference;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.add_request);
        attachButton = findViewById(R.id.attach_button);

        btnRHome = (ImageButton) findViewById(R.id.RequestHome);
        btnRSearch = (ImageButton) findViewById(R.id.RequestSearch);
        btnRProfile = (ImageButton) findViewById(R.id.RequestProfile);

        ConstructButton();
        ClickButtonInRequest();
        initifinal();
        addListenerOnButton();
        addListenerOnSpinnerItemSelection();
        addListenerOnButton();
        CreateAndShowInfoStudent();
    }

    private void ClickButtonInRequest() {
        btnRequestProcessing.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(RequestAdd.this, RequestProcessing.class));
            }
        });

        btnRHome.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(RequestAdd.this, MainActivity.class));
            }
        });

        btnRSearch.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(RequestAdd.this, Search.class));
            }
        });

        btnRProfile.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(RequestAdd.this, Profile.class));
            }
        });
    }

    private void ConstructButton() {
        btnRequestProcessing = (LinearLayout) findViewById(R.id.request_handing_bar);
    }

    private void addListenerOnButton() {
        attachButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
                intent.setType("*/*");
                startActivityForResult(intent, PICKFILE_REQUEST_CODE);
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == PICKFILE_REQUEST_CODE && resultCode == RESULT_OK && data != null && data.getData() != null) {
            Uri uri = data.getData();
            path = getRealPathFromURI(uri);
            // Đính kèm tệp đó vào email, tin nhắn hoặc in-app storage của ứng dụng
        }
    }

    private String getRealPathFromURI(Uri contentUri) {
        String[] projection = { MediaStore.Images.Media.DATA };
        Cursor cursor = getContentResolver().query(contentUri, projection, null, null, null);
        if (cursor == null) return null;
        int columnIndex = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
        cursor.moveToFirst();
        String path = cursor.getString(columnIndex);
        cursor.close();
        return path;
    }

    private void addListenerOnSpinnerItemSelection() {
        spinner1.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                Toast.makeText(getApplicationContext(),"OnItemSelectedListener: " + adapterView.getItemAtPosition(i).toString(), Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {

            }
        });
    }

    private void initifinal() {
        spinner1 = (Spinner) findViewById(R.id.request_type_select);
    }

    public void submitRequest(View view) {
        // Lấy dữ liệu từ Spinner
        Spinner requestTypeSpinner = findViewById(R.id.request_type_select);
        String requestType = requestTypeSpinner.getSelectedItem().toString();

        // Lấy dữ liệu từ EditText
        EditText editTextTitle = findViewById(R.id.request_reason);
        String title = editTextTitle.getText().toString();

        // Gửi dữ liệu lên server
        // Code để gửi dữ liệu lên server

        // Sử dụng thư viện Volley để gửi POST request
        String url = "https://j1-student-connect-default-rtdb.asia-southeast1.firebasedatabase.app";
        StringRequest request = new StringRequest(Request.Method.POST, url,
                new com.android.volley.Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        Toast.makeText(RequestAdd.this, "Request submitted", Toast.LENGTH_SHORT).show();
                    }
                },
                new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                        Toast.makeText(RequestAdd.this, "Error submitting request", Toast.LENGTH_SHORT).show();
                    }
                }) {
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                // Truyền dữ liệu vào request
                Map<String, String> params = new HashMap<>();
                params.put("request_type", requestType);
                params.put("title", title);
                params.put("attachment", path); // Thêm đường dẫn của tệp đính kèm vào request
                // Thêm các tham số khác nếu cần
                return params;
            }
        };
        Volley.newRequestQueue(this).add(request);
    }

    private void CreateAndShowInfoStudent() {
        InfoAddRequest = findViewById(R.id.InfoAddRequest);
        //Intent intentBefore = getActivity().getIntent();
        //String student_id_child = intentBefore.getStringExtra("student_id").toString();
        String student_id_child = "12345678";
        reference = FirebaseDatabase.getInstance("https://j1-student-connect-default-rtdb.asia-southeast1.firebasedatabase.app/").getReference("1srn9ku9VkZvIf9dugTTPEcr2tRk3tkWl0MWxjzT1lp0").child("users").child(student_id_child);
        reference.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                if (snapshot.hasChildren()){
                    String strshow = "Họ tên SV: " + snapshot.child("name").getValue().toString() + "\nMSSV: " + snapshot.child("student_id").getValue().toString();
                    InfoAddRequest.setText(strshow);
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
            }
        });
    }



}