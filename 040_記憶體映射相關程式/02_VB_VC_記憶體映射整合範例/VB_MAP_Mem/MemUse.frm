VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "MemUse - �ϥΡu�@�ΰO����v"
   ClientHeight    =   945
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5250
   LinkTopic       =   "Form1"
   ScaleHeight     =   945
   ScaleWidth      =   5250
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   240
      Width           =   3255
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Ū��"
      Height          =   375
      Left            =   3840
      TabIndex        =   0
      Top             =   240
      Width           =   1095
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim hFileMap As Long
Dim lpView As Long

Private Sub Command1_Click()
    Dim S As String * 80
    
    If lpView <> 0 Then
        ' Ū�� 80 �Ӧr��
        RtlMoveMemory ByVal S, ByVal lpView, 80
        Text1.Text = S
    End If
End Sub

Private Sub Form_Load()
    ' �}�ҦW�٬� "MemMap" ���@�ΰO����
    'hFileMap = OpenFileMapping(FILE_MAP_READ Or FILE_MAP_WRITE, False, "MemMap")
    hFileMap = OpenFileMapping(FILE_MAP_READ Or FILE_MAP_WRITE, False, "spacesoft corp.")
    If hFileMap = 0 Then
        MsgBox "�L�k�}�ҦW�٬� ""MemMap"" ���@�ΰO����"
    Else
        lpView = MapViewOfFile(hFileMap, FILE_MAP_READ Or FILE_MAP_WRITE, 0, 0, 0)
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    CloseHandle hFileMap
End Sub
