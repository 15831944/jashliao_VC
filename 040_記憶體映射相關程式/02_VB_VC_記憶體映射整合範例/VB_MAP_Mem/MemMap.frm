VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "MemMap - �Q�u�O�����M�ɮסv�F���O����@��"
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
      Caption         =   "�e �X"
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
    Dim S As String, hWndRecv As Long, Length As Long
    
    ' �N Text1.Text �ƻs�� lpView ��}
    S = Text1.Text
    Length = LenB(StrConv(S, vbFromUnicode))
    RtlMoveMemory ByVal lpView, ByVal S, Length
    'hWndRecv = FindWindow(0&, "MemRecv - �@�ΰO�����Ʊ�����")
    
    ' wParam �ǤJ Text1.Text ����ƪ���, lParam �h�ǤJ�@�ΰO���骺��}
    'SendMessage hWndRecv, WM_USER + 1003, Length, ByVal lpView
End Sub

Private Sub Form_Load()
    Dim sa As SECURITY_ATTRIBUTES
    
    sa.nLength = Len(sa)
    sa.lpSecurityDescriptor = 0
    sa.bInheritHandle = True

    'hFileMap = CreateFileMapping(-1, sa, PAGE_READWRITE, 0, 1024, "MemMap")
    hFileMap = CreateFileMapping(-1, sa, PAGE_READWRITE, 0, 1024, "spacesoft corp.")
    If GetLastError = ERROR_ALREADY_EXISTS Then
        MsgBox """MemMap"" �w�s�b�A�N�ϥάJ���O����I"
    End If
    lpView = MapViewOfFile(hFileMap, FILE_MAP_READ Or FILE_MAP_WRITE, 0, 0, 0)
    RtlMoveMemory ByVal lpView, ByVal "Data Set by MemMap", 18
End Sub

Private Sub Form_Unload(Cancel As Integer)
    ' CloseHandle hFileMap
End Sub
