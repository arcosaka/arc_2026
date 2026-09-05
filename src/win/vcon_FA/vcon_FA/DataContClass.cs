using System.Runtime.InteropServices;

namespace vcon_FA {

    public class DataContClass {
        public static byte[] ToBytes(DataCont data) {
            int size = Marshal.SizeOf<DataCont>();

            byte[] bytes = new byte[size];

            IntPtr ptr = Marshal.AllocHGlobal(size);

            try {
                Marshal.StructureToPtr(data, ptr, false);
                Marshal.Copy(ptr, bytes, 0, size);
            }
            finally {
                Marshal.FreeHGlobal(ptr);
            }

            return bytes;
        }

        public static DataCont FromBytes(byte[] bytes) {
            IntPtr ptr = Marshal.AllocHGlobal(bytes.Length);

            try {
                Marshal.Copy(bytes, 0, ptr, bytes.Length);
                return Marshal.PtrToStructure<DataCont>(ptr);
            }
            finally {
                Marshal.FreeHGlobal(ptr);
            }
        }
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct DataCont {
        public ushort Header;
        public ushort Stamp;
        public ButtonBits Btns;
        public ushort Checksum;
        public ushort Footer;
    }

    public struct ButtonBits(ushort word) {
        public ushort Word {
            readonly get => word;
            set => word = value;
        }

        public bool IsFull {
            readonly get => (word & (1 << 0)) != 0;
            set => SetBit(0, value);
        }

        public bool XUp {
            readonly get => (word & (1 << 1)) != 0;
            set => SetBit(1, value);
        }

        public bool XRight {
            readonly get => (word & (1 << 2)) != 0;
            set => SetBit(2, value);
        }

        public bool XDown {
            readonly get => (word & (1 << 3)) != 0;
            set => SetBit(3, value);
        }

        public bool XLeft {
            readonly get => (word & (1 << 4)) != 0;
            set => SetBit(4, value);
        }

        public bool BtnX {
            readonly get => (word & (1 << 5)) != 0;
            set => SetBit(5, value);
        }

        public bool BtnA {
            readonly get => (word & (1 << 6)) != 0;
            set => SetBit(6, value);
        }

        public bool BtnB {
            readonly get => (word & (1 << 7)) != 0;
            set => SetBit(7, value);
        }

        public bool BtnY {
            readonly get => (word & (1 << 8)) != 0;
            set => SetBit(8, value);
        }

        public bool L1 {
            readonly get => (word & (1 << 9)) != 0;
            set => SetBit(9, value);
        }

        public bool R1 {
            readonly get => (word & (1 << 10)) != 0;
            set => SetBit(10, value);
        }

        public bool L2 {
            readonly get => (word & (1 << 11)) != 0;
            set => SetBit(11, value);
        }

        public bool R2 {
            readonly get => (word & (1 << 12)) != 0;
            set => SetBit(12, value);
        }

        public bool L3 {
            readonly get => (word & (1 << 13)) != 0;
            set => SetBit(13, value);
        }

        public bool R3 {
            readonly get => (word & (1 << 14)) != 0;
            set => SetBit(14, value);
        }

        private void SetBit(int bit, bool value) {
            if(value) {
                word |= (ushort)(1 << bit);
            }
            else {
                word &= (ushort)~(1 << bit);
            }
        }
    }
}
