## Hospital Management System Code Report
#### Overview
This code implements a basic Hospital Management System using C++. It handles various operations related to doctors, patients, radiology, and appointments. The system includes functionalities for managing doctor and patient records, setting and viewing appointments, and booking radiology scans.

##### Key Components and Functionalities
Structures and Classes:

Radiology: Manages radiologist details such as name, years of experience, room number, patient number, type of radiology scan, and a counter.
Appointment: Manages appointment details including date and time.
Doctor: Contains doctor details including name, age, specialization, and appointment information.
MedicalHistory: Stores medical history details like allergies and medications.
Patient: Manages patient details including name, ID, insurance number, age, blood type, and medical history.
Functions:

##### Main Function:

Initializes doctor and patient lists.
Initializes radiology data.
Adds sample data for patients, doctors, and appointments.
Prompts the user for login and handles different cases for patients and doctors.
Provides menus for different functionalities based on user role (patient, doctor).
Patient Section:

Allows patients to view doctors, take appointments, see available appointments, search for doctors by specialization or name, delete appointments, and access the radiology section.
Doctor Section:

Allows doctors to view patient lists, add medical history, view appointments, and list patients with specific blood types.
Radiology Section:

Allows users to view radiologist details, book radiology scans, and sort radiologists by years of experience.
