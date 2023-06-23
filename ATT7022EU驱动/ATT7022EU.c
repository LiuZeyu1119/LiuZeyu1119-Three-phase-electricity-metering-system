
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/mutex.h>

#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/list.h>
#include <linux/module.h>

#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/init.h>

#include <linux/iio/iio.h>

#include <linux/iio/sysfs.h>
#include "meter.h"
#include "ATT7022EU.h"
long BmToYm(long value)
{
    if((value|0xff7fffff)==0xff7fffff);
    else if((value&0x00800000)==0x00800000)
        value=(~value+1)&0x007fffff;
    
	return value;   
}
static int ATT7022EU_spi_write_reg_24(struct device *dev,
		u16 reg_address,
		u32 value)
{
	printk("[FUNC:]ATT7022EU_spi_write_reg_24");
	int ret;
	//struct spi_message msg;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ATT7022EU_state *st = iio_priv(indio_dev);
	struct spi_transfer xfer = {
		.tx_buf = st->tx,
		.bits_per_word = 8,
		.len = 4,
     //	.delay_usecs = 30,
	};
	printk("write:ADR:%x,VAL:%x",reg_address,value);
	mutex_lock(&st->buf_lock);
	reg_address |= ATT7022EU_WRITE_REG;
	st->tx[0] = reg_address;//ATT7022EU_WRITE_REG | reg_address;
	printk("tx0:0x%02x",st->tx[0]);
	st->tx[1] = (value >> 16) & 0xFF;
	printk("tx1:0x%02x",st->tx[1]);
	st->tx[2] = (value >> 8) & 0xFF;
	printk("tx2:0x%02x",st->tx[2]);
	st->tx[3] = value & 0xFF;
	printk("tx3:0x%02x",st->tx[3]);

	ret = spi_sync_transfer(st->spi, &xfer, 1);
	mutex_unlock(&st->buf_lock);
	printk("[FUNCEND]");
	return ret;
}
static int ATT7022EU_spi_read_reg_24(struct device *dev,
		u16 reg_address,
		u32 *val)
{
	printk("[FUNC:]ATT7022EU_spi_read_reg_24");
	struct spi_message msg;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ATT7022EU_state *st = iio_priv(indio_dev);
	int ret;

	struct spi_transfer xfers[] = {
		{
			.tx_buf = st->tx,
			.bits_per_word = 8,
			.len = 1,
			//.delay_usecs = 2,
		}, {
			.rx_buf = st->rx,
			.bits_per_word = 8,
			.len = 3,
			.delay_usecs = 2,
		}
	};
	printk("spi_read_reg_24 mutex_lock");

	mutex_lock(&st->buf_lock);
	printk("&st->buf_lock");
	st->tx[0] = reg_address&0x7F;
	printk("tx0:0x%02x",st->tx[0]);

	ret = spi_sync_transfer(st->spi, xfers, ARRAY_SIZE(xfers));


	if (ret < 0) {
		dev_err(&st->spi->dev, "problem when reading 24 bit register 0x%02X",
				reg_address);
		goto error_ret;
	}
	*val = (st->rx[0] << 16) | (st->rx[1] << 8) | st->rx[2];
	
	printk("rx0:0x%02x",st->rx[0]);
	printk("rx1:0x%02x",st->rx[1]);
	printk("rx2:0x%02x",st->rx[2]);
	printk("read:ADR:%x,VAL:%x",reg_address,*val);
	printk("[FUNCEND]");

error_ret:
	mutex_unlock(&st->buf_lock);
	return ret;
}

static int ATT7022EU_spi_probe(struct spi_device *spi)
{
	printk("ATT7022EU_spi_probe");
	int ret;
	struct ATT7022EU_state *st;
	struct iio_dev *indio_dev;
	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	st = iio_priv(indio_dev);

	spi_set_drvdata(spi, indio_dev);
	st->read_reg_24 = ATT7022EU_spi_read_reg_24;
	st->write_reg_24 = ATT7022EU_spi_write_reg_24;
	st->irq = spi->irq;
	st->spi = spi;
	st->spi->max_speed_hz = 1000000;
	st->spi->mode = SPI_MODE_1;
	
	spi_setup(st->spi); 

	return ATT7022EU_probe(indio_dev, &spi->dev);
	//printk("spi probe ret %d",ret);
	if (ret) {
		kfree(st);	
		struct ATT7022EU_state *st = kzalloc(sizeof *st, GFP_KERNEL);
	if (!st) {
		ret =  -ENOMEM;
		return ret;
	}

		return ret;
	}

	return 0;
}

static int ATT7022EU_spi_remove(struct spi_device *spi)
{
	printk(KERN_WARNING "att7022EU_spi_remove");
	ATT7022EU_remove(spi_get_drvdata(spi));

	return 0;
}
/* 传统匹配方式ID列表 */
static const struct spi_device_id ATT7022EU_id[] = {
	{ "ATT7022EU", 0 },
	{ }
};
/* device tree匹配列表 */
static const struct of_device_id ATT7022EU_of_match[] = {
    {.compatible = "ATT7022EU,ATT7022EU"},
    {/* Sentinel */}
};


static struct spi_driver ATT7022EU_driver = {
	.probe = ATT7022EU_spi_probe,
	.remove = ATT7022EU_spi_remove,
	.driver = {
		.name = "ATT7022EU",
		.owner = THIS_MODULE,
		.of_match_table = ATT7022EU_of_match,  /* 设备树匹配列表 */
	},
	.id_table = ATT7022EU_id,
};
/*__init*/
static int __init ATT7022EU_init(void)
{
	printk(KERN_WARNING "Att7022EU_init");
	int ret = spi_register_driver(&ATT7022EU_driver);

	printk("register %d",ret);
	return ret;
}
module_init(ATT7022EU_init);

/*__exit*/
static void __exit ATT7022EU_exit(void)
{
	printk(KERN_WARNING"Att7022EU_exit");
	spi_unregister_driver(&ATT7022EU_driver);
}
module_exit(ATT7022EU_exit);


static ssize_t ATT7022EU_read_24bit(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{	
	printk("ATT7022EU_read_24bit");
	int ret;
	u32 val ;
	//float result;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ATT7022EU_state *st = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	st->write_reg_24(dev, 0xC6,0x00015a);
	usleep_range(50,50);

	ret = st->read_reg_24(dev, this_attr->address, &val);
	printk("read 24bit ret :%d",ret);
	if (ret)
		return ret;
	//return 1;
	return sprintf(buf, "%u\n",val);
}

static ssize_t ATT7022EU_write_24bit(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t len)
{
	printk("ATT7022EU_write_24bit");
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ATT7022EU_state *st = iio_priv(indio_dev);

	int ret;
	u32 val;

	ret = kstrtou32(buf, 10, &val);
	if (ret)
		goto error_ret;
	ret = st->write_reg_24(dev, this_attr->address, val);
	printk("write ret:%d",ret);
error_ret:
	return ret ? ret : len;
}

static int ATT7022EU_reset(struct device *dev)
{
	printk("ATT7022EU_reset");
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	printk("iio_dev *indio_dev = dev_to_iio_dev(dev);");
	struct ATT7022EU_state *st = iio_priv(indio_dev);
	printk("ATT7022EU_state *st = iio_priv(indio_dev);");

	//u32 val = 0x00000000;
	//printk("val:%d",val);
	u16 val16;
	val16 = 0x00000000; /* Software Chip Reset */
	printk("val16:%d",val16);
	/*soft reset*/
	printk("reset");
	
	//return ATT7022EU_spi_write_reg_24(dev, ATT7022EU_RESET, 0x00000000);
	return st->write_reg_24(dev, 0xD3, val16);

}

static IIO_DEVICE_ATTR(dev_id, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		0x00, ATT7022EU_DEV_ID);
static IIO_DEVICE_ATTR(chip_id, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		0x00, 0x5D);
static IIO_DEVICE_ATTR(pa, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PA);
static IIO_DEVICE_ATTR(pb, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PB);
static IIO_DEVICE_ATTR(pc, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PC);
static IIO_DEVICE_ATTR(pt, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PT);

static IIO_DEVICE_ATTR(qa, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_QA);
static IIO_DEVICE_ATTR(qb, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_QB);
static IIO_DEVICE_ATTR(qc, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_QC);
static IIO_DEVICE_ATTR(qt, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_QT);

static IIO_DEVICE_ATTR(sa, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_SA);
static IIO_DEVICE_ATTR(sb, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_SB);
static IIO_DEVICE_ATTR(sc, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_SC);
static IIO_DEVICE_ATTR(st, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_ST);

static IIO_DEVICE_ATTR(uarms, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_UARMS);
static IIO_DEVICE_ATTR(ubrms, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_UBRMS);
static IIO_DEVICE_ATTR(ucrms, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_UCRMS);

static IIO_DEVICE_ATTR(iarms, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_IARMS);
static IIO_DEVICE_ATTR(ibrms, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_IBRMS);
static IIO_DEVICE_ATTR(icrms, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_ICRMS);
static IIO_DEVICE_ATTR(itrms, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_ITRMS);

static IIO_DEVICE_ATTR(pfa, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PFA);
static IIO_DEVICE_ATTR(pfb, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PFB);
static IIO_DEVICE_ATTR(pfc, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PFC);
static IIO_DEVICE_ATTR(pft, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PFT);

static IIO_DEVICE_ATTR(pga, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PGA);
static IIO_DEVICE_ATTR(pgb, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PGB);
static IIO_DEVICE_ATTR(pgc, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PGC);

static IIO_DEVICE_ATTR(intflag, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_INTFLAG);
static IIO_DEVICE_ATTR(freq, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_FREQ);
static IIO_DEVICE_ATTR(eflag, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_EFLAG);

static IIO_DEVICE_ATTR(epa, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_EPA);
static IIO_DEVICE_ATTR(epb, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_EPB);
static IIO_DEVICE_ATTR(epc, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_EPC);
static IIO_DEVICE_ATTR(ept, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_EPT);

static IIO_DEVICE_ATTR(eqa, S_IWUSR | S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_EQA);
static IIO_DEVICE_ATTR(eqb, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_EQB);
static IIO_DEVICE_ATTR(eqc, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_EQC);
static IIO_DEVICE_ATTR(eqt, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_EQT);

static IIO_DEVICE_ATTR(yuaub, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_YUAUB);
static IIO_DEVICE_ATTR(yuauc, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_YUAUC);
static IIO_DEVICE_ATTR(yubuc, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_YUBUC);

static IIO_DEVICE_ATTR(i0rms, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_I0RMS);
static IIO_DEVICE_ATTR(tpsd0, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_TPSD0);
static IIO_DEVICE_ATTR(utrms, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_UTRMS);
static IIO_DEVICE_ATTR(sflag, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_SFLAG);
static IIO_DEVICE_ATTR(bckreg, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_BCKREG);
static IIO_DEVICE_ATTR(cmdchksum, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_CMDCHKSUM);

static IIO_DEVICE_ATTR(sample_ia, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_SAMPLE_IA);
static IIO_DEVICE_ATTR(sample_ib, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_SAMPLE_IB);
static IIO_DEVICE_ATTR(sample_ic, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_SAMPLE_IC);
static IIO_DEVICE_ATTR(sample_ua, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_SAMPLE_UA);
static IIO_DEVICE_ATTR(sample_ub, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_SAMPLE_UB);
static IIO_DEVICE_ATTR(sample_uc, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_SAMPLE_UC);

static IIO_DEVICE_ATTR(esa, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_ESA);
static IIO_DEVICE_ATTR(esb, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_ESB);
static IIO_DEVICE_ATTR(esc, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_ESC);
static IIO_DEVICE_ATTR(est, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_EST);

static IIO_DEVICE_ATTR(fstcnta, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_FSTCNTA);
static IIO_DEVICE_ATTR(fstcntb, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_FSTCNTB);
static IIO_DEVICE_ATTR(fstcntc, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_FSTCNTC);
static IIO_DEVICE_ATTR(fstcntt, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_FSTCNTT);

static IIO_DEVICE_ATTR(pflag, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PFLAG);
static IIO_DEVICE_ATTR(chksum, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_CHKSUM);
static IIO_DEVICE_ATTR(sample_io, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_SAMPLE_I0);

static IIO_DEVICE_ATTR(linepa, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEPA);
static IIO_DEVICE_ATTR(linepb, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEPB);
static IIO_DEVICE_ATTR(linepc, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEPC);
static IIO_DEVICE_ATTR(linept, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEPT);
static IIO_DEVICE_ATTR(lineepa, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEEPA);
static IIO_DEVICE_ATTR(lineepb, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEEPB);
static IIO_DEVICE_ATTR(lineepc, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEEPC);
static IIO_DEVICE_ATTR(lineept, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEEPT);

static IIO_DEVICE_ATTR(lineuarrms, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEUARRMS);
static IIO_DEVICE_ATTR(lineubrrms, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEUBRRMS);
static IIO_DEVICE_ATTR(lineucrrms, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEUCRRMS);
static IIO_DEVICE_ATTR(lineiarrms, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEIARRMS);
static IIO_DEVICE_ATTR(lineibrrms, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEIBRRMS);
static IIO_DEVICE_ATTR(lineicrrms, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LINEICRRMS);

static IIO_DEVICE_ATTR(leflag, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_LEFLAG);
static IIO_DEVICE_ATTR(ptrwavebuff, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_PTRWAVEBUFF);
static IIO_DEVICE_ATTR(wavebuff, S_IRUGO, ATT7022EU_read_24bit,
		NULL, ATT7022EU_WAVEBUFF);

static int ATT7022EU_set_irq(struct device *dev, bool enable)
{
	printk("ATT7022EU_set_irq");
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ATT7022EU_state *st = iio_priv(indio_dev);

	int ret;
	u32 irqen = 0 ;

	ret = st->read_reg_24(dev, ATT7022EU_INTFLAG, &irqen);
	if (ret)
		return ret;
	printk("ATT7022EU_set_irq ret:%d",ret);
	if (enable)
		irqen |= BIT(17); /* 1: interrupt enabled when all periodical
				   * (at 8 kHz rate) DSP computations finish.
				   */
	else
		irqen &= ~BIT(17);

	return st->write_reg_24(dev, ATT7022EU_INTFLAG, irqen);
return -1;
//error_ret:
//	return ret;
}

void  readSimpleRegister(struct device *dev,
		u16 reg_address,
		u32 value){
	int ret;
	int val;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ATT7022EU_state *st = iio_priv(indio_dev);
	

}

int writerAdjustRegisterCheck(struct device *dev,
		u16 reg_address,
		u32 value)
{
	int ret;
	int val;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ATT7022EU_state *st = iio_priv(indio_dev);
	st->write_reg_24(dev,0xc9,0x00005A);
	st->write_reg_24(dev,reg_address,value);	
	printk("**write check:ADR:0x%02x,VAL:0x%02x**",reg_address,value);
	st->write_reg_24(dev,0xc9,0x00015A);
	msleep(200);
	st->write_reg_24(dev,0xc6,0x00005A);
	st->read_reg_24(dev,reg_address,&val);
	st->write_reg_24(dev,0xc6,0x00015A);
	printk("**write check:ADR:0x%02x**",val);
	if(val ==  value){
		return 1;
	}
	return 0;
}

static int ATT7022EU_initial_setup(struct iio_dev *indio_dev)
{
	printk("ATT7022EU_initial_setup");
	int ret = 0;
	//struct device *dev = &st->indio_dev->dev;
	struct device *dev = &indio_dev->dev;
	struct ATT7022EU_state *st = iio_priv(indio_dev);
	/*Disable IRQ*/ 
	/*ret = ATT7022EU_set_irq(dev, false);
	if (ret) {
		dev_err(dev, "disable irq failed");
	//	goto err_ret;
	}*/
	printk("initting ...");
	ATT7022EU_reset(dev);
	printk("msleep:%d ms",ATT7022EU_STARTUP_DELAY);
	msleep(ATT7022EU_STARTUP_DELAY);
	//校表
	u32 val = 0;
	st->write_reg_24(dev, 0xc3, 0x000000);
	//msleep(200);
	while(writerAdjustRegisterCheck(dev,0x01,0x00B97E) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}
	while(writerAdjustRegisterCheck(dev,0x02,0x000000) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}
	while(writerAdjustRegisterCheck(dev,0x03,0x00F884) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}
	while(writerAdjustRegisterCheck(dev,0x31,0x003427) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}
	while(writerAdjustRegisterCheck(dev,0x1e,0x000016) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

	while(writerAdjustRegisterCheck(dev,0x17+0x00,0x005FD0) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

		while(writerAdjustRegisterCheck(dev,0x17+0x01,0x005F18) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

	while(writerAdjustRegisterCheck(dev,0x17+0x02,0x005CC5) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

	while(writerAdjustRegisterCheck(dev,0x1A+0x00,0x006292) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

		while(writerAdjustRegisterCheck(dev,0x1A+0x01,0x00629D) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

	while(writerAdjustRegisterCheck(dev,0x1A+0x02,0x006260) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

		while(writerAdjustRegisterCheck(dev,0x04+0x00,0x001E7B) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

		while(writerAdjustRegisterCheck(dev,0x04+0x01,0x001DFA) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

	while(writerAdjustRegisterCheck(dev,0x04+0x02,0x001C25) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

		while(writerAdjustRegisterCheck(dev,0x07+0x00,0x001E7B) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

		while(writerAdjustRegisterCheck(dev,0x07+0x01,0x001DFA) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

	while(writerAdjustRegisterCheck(dev,0x07+0x02,0x001C25) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}
	while(writerAdjustRegisterCheck(dev,0x0A+0x00,0x001E7B) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

    while(writerAdjustRegisterCheck(dev,0x0A+0x01,0x001DFA) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}

	while(writerAdjustRegisterCheck(dev,0x0A+0x02,0x001C25) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}



	/*while(writerAdjustRegisterCheck(dev,0xc5,0x000000) != 1){
		 printk("check error!");
		 msleep(1);
	}

	while(writerAdjustRegisterCheck(dev,0xc5,0x000002) != 1) {
		 printk("check error!");
		 msleep(1);
		 }*/
	/*while(writerAdjustRegisterCheck(dev,0xc5,0x000002) != 1)
	{
		 printk("check error!");
		 msleep(1);
	}*/
	//msleep(1);

	//st->write_reg_24(dev, 0xc6, 0x000000);
	//printk("ATT7022EU init success val:%d",val);
err_ret:
	return ret;
}

//static IIO_DEV_ATTR_RESET(ATT7022EU_write_reset);

static IIO_CONST_ATTR_SAMP_FREQ_AVAIL("8000");

static IIO_CONST_ATTR(name, "ATT7022EU");

static struct attribute *ATT7022EU_attributes[] = {
	&iio_dev_attr_dev_id.dev_attr.attr,
	&iio_dev_attr_chip_id.dev_attr.attr,
	&iio_dev_attr_pa.dev_attr.attr,
	&iio_dev_attr_pb.dev_attr.attr,
	&iio_dev_attr_pc.dev_attr.attr,
	&iio_dev_attr_pt.dev_attr.attr,
	&iio_dev_attr_qa.dev_attr.attr,
	&iio_dev_attr_qb.dev_attr.attr,
	&iio_dev_attr_qc.dev_attr.attr,
	&iio_dev_attr_qt.dev_attr.attr,
	&iio_dev_attr_sa.dev_attr.attr,
	&iio_dev_attr_sb.dev_attr.attr,
	&iio_dev_attr_sc.dev_attr.attr,
	&iio_dev_attr_st.dev_attr.attr,

	&iio_dev_attr_uarms.dev_attr.attr,
	&iio_dev_attr_ubrms.dev_attr.attr,
	&iio_dev_attr_ucrms.dev_attr.attr,
	&iio_dev_attr_iarms.dev_attr.attr,
	&iio_dev_attr_ibrms.dev_attr.attr,
	&iio_dev_attr_icrms.dev_attr.attr,
	&iio_dev_attr_itrms.dev_attr.attr,
	
	&iio_dev_attr_pfa.dev_attr.attr,
	&iio_dev_attr_pfb.dev_attr.attr,
	&iio_dev_attr_pfc.dev_attr.attr,
	&iio_dev_attr_pft.dev_attr.attr,
	&iio_dev_attr_pga.dev_attr.attr,
	&iio_dev_attr_pgb.dev_attr.attr,
	&iio_dev_attr_pgc.dev_attr.attr,

	&iio_dev_attr_intflag.dev_attr.attr,
	&iio_dev_attr_freq.dev_attr.attr,
	&iio_dev_attr_eflag.dev_attr.attr,

	&iio_dev_attr_epa.dev_attr.attr,
	&iio_dev_attr_epb.dev_attr.attr,
	&iio_dev_attr_epc.dev_attr.attr,
	&iio_dev_attr_ept.dev_attr.attr,
	&iio_dev_attr_eqa.dev_attr.attr,
	&iio_dev_attr_eqb.dev_attr.attr,
	&iio_dev_attr_eqc.dev_attr.attr,
	&iio_dev_attr_eqt.dev_attr.attr,

	&iio_dev_attr_yuaub.dev_attr.attr,
	&iio_dev_attr_yuauc.dev_attr.attr,
	&iio_dev_attr_yubuc.dev_attr.attr,

	&iio_dev_attr_i0rms.dev_attr.attr,
	&iio_dev_attr_tpsd0.dev_attr.attr,
	&iio_dev_attr_utrms.dev_attr.attr,
	&iio_dev_attr_sflag.dev_attr.attr,
	&iio_dev_attr_bckreg.dev_attr.attr,
	&iio_dev_attr_cmdchksum.dev_attr.attr,

	&iio_dev_attr_sample_ia.dev_attr.attr,
	&iio_dev_attr_sample_ib.dev_attr.attr,
	&iio_dev_attr_sample_ic.dev_attr.attr,
	&iio_dev_attr_sample_ua.dev_attr.attr,
	&iio_dev_attr_sample_ub.dev_attr.attr,
	&iio_dev_attr_sample_uc.dev_attr.attr,

	&iio_dev_attr_esa.dev_attr.attr,
	&iio_dev_attr_esb.dev_attr.attr,
	&iio_dev_attr_esc.dev_attr.attr,
	&iio_dev_attr_est.dev_attr.attr,
	&iio_dev_attr_fstcnta.dev_attr.attr,
	&iio_dev_attr_fstcntb.dev_attr.attr,
	&iio_dev_attr_fstcntc.dev_attr.attr,
	&iio_dev_attr_fstcntt.dev_attr.attr,

	&iio_dev_attr_pflag.dev_attr.attr,
	&iio_dev_attr_chksum.dev_attr.attr,
	&iio_dev_attr_sample_io.dev_attr.attr,

	&iio_dev_attr_linepa.dev_attr.attr,
	&iio_dev_attr_linepb.dev_attr.attr,
	&iio_dev_attr_linepc.dev_attr.attr,
	&iio_dev_attr_linept.dev_attr.attr,
	&iio_dev_attr_lineepa.dev_attr.attr,
	&iio_dev_attr_lineepb.dev_attr.attr,
	&iio_dev_attr_lineepc.dev_attr.attr,
	&iio_dev_attr_lineept.dev_attr.attr,

	&iio_dev_attr_lineuarrms.dev_attr.attr,
	&iio_dev_attr_lineubrrms.dev_attr.attr,
	&iio_dev_attr_lineucrrms.dev_attr.attr,
	&iio_dev_attr_lineiarrms.dev_attr.attr,
	&iio_dev_attr_lineibrrms.dev_attr.attr,
	&iio_dev_attr_lineicrrms.dev_attr.attr,

	&iio_dev_attr_leflag.dev_attr.attr,
	&iio_dev_attr_ptrwavebuff.dev_attr.attr,
	&iio_dev_attr_wavebuff.dev_attr.attr,
	//&iio_dev_attr_reset.dev_attr.attr,
	&iio_const_attr_name.dev_attr.attr,
	&iio_const_attr_sampling_frequency_available.dev_attr.attr,
	NULL,
};

static const struct attribute_group ATT7022EU_attribute_group = {
	.attrs = ATT7022EU_attributes,
};
/*iio_dev 有个成员变量：info，为 iio_info 结构体指针变量，
这个是我们在编写 IIO 驱动的时候需要着重去实现的，
因为用户空间对设备的具体操作最终都会反映到 iio_info 里面。i
io_info结构体定义在 include/linux/iio/iio.h 中*/
static const struct iio_info ATT7022EU_info = {
	.attrs = &ATT7022EU_attribute_group,

	//.driver_module = THIS_MODULE,
};

int ATT7022EU_probe(struct iio_dev *indio_dev, struct device *dev)
{
	int ret;
	struct ATT7022EU_state *st = iio_priv(indio_dev);
	printk("st");
	/* Allocate the comms buffers */
	printk(KERN_WARNING"att7022EU_probe");
	/* setup the industrialio driver allocated elements */
	mutex_init(&st->buf_lock);

	indio_dev->dev.parent = dev;
	indio_dev->info = &ATT7022EU_info;
	//st->indio_dev->dev_data = (void *)(st);
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = devm_iio_device_register(dev, indio_dev);
	if (ret)
		return ret;

	/* Get the device into a sane initial state */
	return ATT7022EU_initial_setup(indio_dev);

error_free_tx:
	kfree(st->tx);
error_free_rx:
	kfree(st->rx);
error_free_st:
	kfree(st);

}

EXPORT_SYMBOL(ATT7022EU_probe);

int ATT7022EU_remove(struct ATT7022EU_state *st)
{
	struct iio_dev *indio_dev = st->indio_dev;
	printk(KERN_WARNING "att7022EU_remove");
	iio_device_unregister(indio_dev);
	kfree(st->tx);
	kfree(st->rx);
	kfree(st);

	return 0;
}
EXPORT_SYMBOL(ATT7022EU_remove);

MODULE_AUTHOR("Zeyu Liu <helloworldZeyu@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ATT7022EU Polyphase Energy Meter");
MODULE_LICENSE("GPL v2");