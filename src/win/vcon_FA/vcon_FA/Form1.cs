using System.Diagnostics;
using System.IO.Ports;
using System.Runtime.InteropServices;
using static System.Runtime.InteropServices.JavaScript.JSType;


namespace vcon_FA {
    public partial class Form1 : Form {

        const ushort SERIALIO_HEADER = (ushort)0x5A5AU;
        const ushort SERIALIO_FOOTER = (ushort)0x0A0DU;

        DataCont data_tx = new();
        DataCont data_rx = new();
        ushort u2_txcnt = 0;
        readonly Queue<byte[]> queue_rxdata = new();
        readonly SerialPort serialPort = new();
        readonly System.Timers.Timer serialPortTimer = new(10);
        readonly System.Timers.Timer screenUpdateTimer = new(100);

        public Form1() {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e) {
            serialPort.BaudRate = 115200;
            serialPort.Parity = Parity.None;
            serialPort.StopBits = StopBits.One;
            serialPort.DataReceived += SerialPort_DataReceived;
            serialPortTimer.Elapsed += SerialPortTimer_Elapsed;
            screenUpdateTimer.Elapsed += ScreenUpdateTimer_Elapsed;
            screenUpdateTimer.Start();
        }

        private void ScreenUpdateTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e) {
            string str_txt = "";
            while(queue_rxdata.TryDequeue(out byte[] data)) {
                str_txt += $"[RX]{string.Join(",", data.Select(d => d.ToString("X2")))}{Environment.NewLine}";
            }
            AddText(str_txt);
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e) {
            serialPortTimer.Stop();
            serialPortTimer.Start();
        }

        private void SerialPortTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e) {
            serialPortTimer.Stop();
            byte[] buf = new byte[serialPort.BytesToRead];
            serialPort.Read(buf, 0, buf.Length);
            lock(queue_rxdata) {
                queue_rxdata.Enqueue(buf);
            }
        }

        private void ComboBox_Root_ComPort_DropDown(object sender, EventArgs e) {
            ComboBox_Root_ComPort.Items.Clear();
            foreach(var item in SerialPort.GetPortNames()) {
                ComboBox_Root_ComPort.Items.Add(item);
            }
        }

        private void CheckBox_Root_Run_CheckedChanged(object sender, EventArgs e) {
            if(CheckBox_Root_Run.Checked) {
                try {
                    serialPort.PortName = ComboBox_Root_ComPort.Text;
                    serialPort.Open();
                }
                catch(Exception ex) {
                    Debug.WriteLine(ex.Message);
                    CheckBox_Root_Run.Checked = false;
                }
            }
            if(!CheckBox_Root_Run.Checked) {
                try {
                    serialPort.Close();
                }
                catch(Exception ex) {
                    Debug.WriteLine(ex.Message);
                }
            }
            Timer_Root_Send.Enabled = CheckBox_Root_Run.Checked;

        }

        private void Timer_Root_Send_Tick(object sender, EventArgs e) {
            data_tx.Header = SERIALIO_HEADER;
            data_tx.Footer = SERIALIO_FOOTER;
            data_tx.Stamp = u2_txcnt;
            u2_txcnt++;
            if(RadioButton_Root_Full.Checked) {
                data_tx.Btns.IsFull = true;
            }
            else if(RadioButton_Root_Simple.Checked) {
                data_tx.Btns.IsFull = false;
                data_tx.Btns.XUp = CheckBox_Simple_Up.Checked;
                data_tx.Btns.XDown = CheckBox_Simple_Down.Checked;
                data_tx.Btns.XLeft = CheckBox_Simple_Left.Checked;
                data_tx.Btns.XRight = CheckBox_Simple_Right.Checked;
            }
            else {
                CheckBox_Root_Run.Checked = false;
                return;
            }
            data_tx.Checksum = SerialIO_CalcChkSum(DataContClass.ToBytes(data_tx), (Marshal.SizeOf<DataCont>() - 4));
            var byts_tx = DataContClass.ToBytes(data_tx);
            serialPort.Write(byts_tx, 0, byts_tx.Length);

            AddText($"[TX]{string.Join(",", byts_tx.Select(d => d.ToString("X2")))}{Environment.NewLine}");
        }

        private void AddText(string str_txt) {
            if(str_txt != "") {
                TextBox_Root_Data.Invoke(() => {
                    TextBox_Root_Data.Text += str_txt;
                    TextBox_Root_Data.SelectionStart = TextBox_Root_Data.TextLength;
                    TextBox_Root_Data.SelectionLength = 1;
                    TextBox_Root_Data.ScrollToCaret();
                    TextBox_Root_Data.Refresh();
                });
            }
        }

        private static ushort SerialIO_CalcChkSum(byte[] pu1_data, int s4_size = 0) {
            ushort u2_data = 0;
            if(s4_size == 0) {
                s4_size = pu1_data.Length;
            }
            for(byte u1_i = 0; u1_i < s4_size; u1_i++) {
                u2_data += (ushort)pu1_data[u1_i];
            }
            u2_data = (ushort)((uint)0x10000U - (uint)u2_data);
            return u2_data;
        }
    }
}
