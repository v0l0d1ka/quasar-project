USE [PBS_A]
GO
/****** Object:  Trigger [dbo].[myTrig]    Script Date: 04/07/2017 11:07:46 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Golodnii, Vladimir>
-- =============================================
ALTER TRIGGER [dbo].[myTrig] 
   ON   [PBS_A].[dbo].[TiempoMuerto_Detalle]
   AFTER INSERT
AS 
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
    -- Insert statements for trigger here
    DECLARE @cmd varchar(400);
    DECLARE @Activo bit;
    DECLARE @Dep_ID int;
    DECLARE @FechaHoraInitial datetime;
    DECLARE @Maqina varchar(60);
   
    SELECT @Maqina = 'x';
    SELECT @Activo = i.Activo FROM inserted i;
    SELECT @Dep_ID = i.DepartamentoID FROM inserted i;
    SELECT @FechaHoraInitial = i.FechaHoraInicial FROM inserted i;
    SELECT @Maqina = Maquina FROM dbo.TiempoMuerto_Detalle_Mantenimiento 
                             WHERE FechaHora = @FechaHoraInitial;
			SELECT @cmd = 'echo' 
			+ ' ' + CONVERT(varchar(1), @Activo)
			+ ' ' + CONVERT(varchar(1), @Dep_ID) 
		      + ' ' + CONVERT(varchar(3), @Maqina)	
	            + ' n > c:\serial.txt';
    EXEC  master..xp_cmdshell @cmd;
			       
END



USE [PBS_A]
GO
/****** Object:  Trigger [dbo].[myTrigUpdate]    Script Date: 04/07/2017 11:08:08 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Golodnii,,Vladimir>
-- =============================================
ALTER TRIGGER [dbo].[myTrigUpdate] 
   ON  [PBS_A].[dbo].[TiempoMuerto_Detalle] 
   AFTER UPDATE
AS 
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;
    -- Insert statements for trigger here
    DECLARE @cmd varchar(400);
    DECLARE @Activo bit;
    DECLARE @Dep_ID int;
    DECLARE @FechaHoraInitial datetime;    
    DECLARE @Maqina varchar(60);
   
    SELECT @Maqina = 'x';
    SELECT @Activo = i.Activo FROM inserted i;
    SELECT @Dep_ID = i.DepartamentoID FROM inserted i;
    SELECT @FechaHoraInitial = i.FechaHoraInicial FROM inserted i;
    SELECT @Maqina = Maquina FROM dbo.TiempoMuerto_Detalle_Mantenimiento 
                             WHERE FechaHora = @FechaHoraInitial;
    
			SELECT @cmd = 'echo' 
			+ ' ' + CONVERT(varchar(1), @Activo)
			+ ' ' + CONVERT(varchar(1), @Dep_ID) 
		      + ' ' + CONVERT(varchar(3), @Maqina)	
	            + ' n > c:\serial.txt';
    EXEC  master..xp_cmdshell @cmd;	
END
