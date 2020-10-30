using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        private string path_ok;
        private string path_ng;
        private string path_imgs;
        private string path_model;

        public MainWindow()
        {
            InitializeComponent();
            tb_path_ok.Text = "";
            tb_path_ng.Text = "";
            tb_path_model.Text = "";
            tb_path_imgs.Text = "";
        }

        private void run(string filename, string arguments)
        {
            System.Diagnostics.Process p = new System.Diagnostics.Process();
            p.StartInfo.FileName = filename;
            p.StartInfo.Arguments = arguments;
            p.Start();

            if (p.HasExited)
            {
                p.Kill();
            }
        }

        private void bt_ok_Click(object sender, RoutedEventArgs e)
        {
            var ofd = new Microsoft.Win32.OpenFileDialog();
            ofd.Filter = "Folders|\n";
            ofd.FileName = "Folder Selection";
            ofd.CheckPathExists = true;
            ofd.ShowReadOnly = false;
            ofd.ReadOnlyChecked = true;
            ofd.CheckFileExists = false;
            ofd.ValidateNames = false;
            if (ofd.ShowDialog() == true)
            {
                path_ok = System.IO.Path.GetDirectoryName(ofd.FileName);
                tb_path_ok.Text = path_ok;
            }
        }

        private void bt_ng_Click(object sender, RoutedEventArgs e)
        {
            var ofd = new Microsoft.Win32.OpenFileDialog();
            ofd.Filter = "Folders|\n";
            ofd.FileName = "Folder Selection";
            ofd.CheckPathExists = true;
            ofd.ShowReadOnly = false;
            ofd.ReadOnlyChecked = true;
            ofd.CheckFileExists = false;
            ofd.ValidateNames = false;
            if (ofd.ShowDialog() == true)
            {
                path_ng = System.IO.Path.GetDirectoryName(ofd.FileName);
                tb_path_ng.Text = path_ng;
            }
        }

        private void bt_train_Click(object sender, RoutedEventArgs e)
        {
            string filename = @"trainer.exe";
            string args = " --method=2 --graph=./model/mckp/train/model " +
                "--config=./tf_train.ini --ok=" + path_ok + "/" + 
                " --ng=" + path_ok + "/";
            run(filename, args);
        }

        private void bt_img_Click(object sender, RoutedEventArgs e)
        {
            var ofd = new Microsoft.Win32.OpenFileDialog();
            ofd.Filter = "Folders|\n";
            ofd.FileName = "Folder Selection";
            ofd.CheckPathExists = true;
            ofd.ShowReadOnly = false;
            ofd.ReadOnlyChecked = true;
            ofd.CheckFileExists = false;
            ofd.ValidateNames = false;
            if (ofd.ShowDialog() == true)
            {
                path_imgs = System.IO.Path.GetDirectoryName(ofd.FileName);
                tb_path_imgs.Text = path_imgs;
            }
        }

        private void bt_model_Click(object sender, RoutedEventArgs e)
        {
            var ofd = new Microsoft.Win32.OpenFileDialog();
            ofd.Filter = "Folders|\n";
            ofd.FileName = "Folder Selection";
            ofd.CheckPathExists = true;
            ofd.ShowReadOnly = false;
            ofd.ReadOnlyChecked = true;
            ofd.CheckFileExists = false;
            ofd.ValidateNames = false;
            if (ofd.ShowDialog() == true)
            {
                path_model = System.IO.Path.GetDirectoryName(ofd.FileName);
                tb_path_model.Text = path_model;
            }
        }

        private void bt_test_Click(object sender, RoutedEventArgs e)
        {
            string filename = @"classifier.exe";
            string args = " --graph=./model/mckp/test/model --batch=1 --method=2 " +
                "--factor=1  --input_height=128 --input_width=128 --window_height=128 " +
                "--window_width=128  --file_path=NG/ --save_image=3";
            run(filename, args);
        }
    }
}
